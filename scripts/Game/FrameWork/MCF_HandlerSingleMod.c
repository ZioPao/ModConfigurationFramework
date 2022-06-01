class MCF_HandlerSingleMod : ScriptedWidgetComponent
{
	
	//todo make layout for single mod settings
	static const string MOD_SETTINGS_LAYOUT_PATH = "{1D2D036656276994}UI/layouts/Menus/SettingsMenu/ModSettings.layout";
	static const string MOD_SINGLE_SETTING_LAYOUT_PATH = "{271E5986CD528C3B}UI/layouts/WidgetLibrary/EditBox/MCF_EditBox.layout";
	
	ref map<string, string> modVariables;
	
	string modId;
	
	
	void MCF_HandlerSingleMod(string id)
	{
		this.modId = id;
	}


	override bool OnClick(Widget w, int x, int y, int button)
	{
		// Should open another dialog menu I guess, or something on the right or whatever. Still, we need to load the specific settings for this mod. 
		
		
		VerticalLayoutWidget descriptionLayout = VerticalLayoutWidget.Cast(w.GetParent().GetParent().GetParent().FindAnyWidget("Description"));
		//Print(TextWidget.Cast(w.FindAnyWidget("TextMod")).GetText());
		
		Widget oldWidget = descriptionLayout.GetChildren();
		
		
		if (oldWidget)
			descriptionLayout.RemoveChild(oldWidget);
		
		

		Widget singleModMenu = GetGame().GetWorkspace().CreateWidgets(MOD_SETTINGS_LAYOUT_PATH, descriptionLayout);
		TextWidget modLabel = TextWidget.Cast(singleModMenu.FindAnyWidget("ModLabel"));
		TextWidget oldTextWidget = TextWidget.Cast(w.FindAnyWidget("TextMod"));
		string oldText = oldTextWidget.GetText();
		modLabel.SetText(oldText);

		
		VerticalLayoutWidget settingsLayout = VerticalLayoutWidget.Cast(singleModMenu.FindAnyWidget("SettingsLayout"));
		
		
		
		
		MCF_SettingsManager settingsManager = MCF_SettingsManager.GetInstance();
		modVariables = settingsManager.GetModSettings(modId);	
		
		MCF_JsonManager jsonManager = settingsManager.GetJsonManager(modId);
		//Print(modVariables);
		
		
		

		
		int index = 0;
		
		foreach(string varName, string varValue : modVariables)
		{
			Widget tempWidget  = GetGame().GetWorkspace().CreateWidgets(MOD_SINGLE_SETTING_LAYOUT_PATH, settingsLayout);
			MCF_EditBoxComponent editBoxComponent = MCF_EditBoxComponent.Cast(tempWidget.FindHandler(MCF_EditBoxComponent));
			
			Print(varName);
			Print(varValue);
			Print("__________");
			
			
			editBoxComponent.ReferenceModVariables(modVariables);
			string tempName = jsonManager.userFriendlyKeys[index];
			editBoxComponent.SetSetting(tempName, varValue);
			editBoxComponent.SetCurrentJsonManager(jsonManager);
			index++;

			
		}
		

		return true;
		
	}
	
	
	
	void PopulateSettings()
	{
		// Search for correct json 
		
		
		
	}
	
	
	void ApplyChanges()
	{
		
		//when we apply a setting, we need to reload the mod... or not? 
		// no we don't need to reload anything if it's loaded directly from a json... but probably it'll be slower I guess?
		// we'd probably need some kind of interface to load json ONCE at apply time and then forget about them at runtime 
		
		
		// We'll make a callback to something connected to every compatible mod. That callback will start a re-read of changed values in the json
		
	}
	
	

}



