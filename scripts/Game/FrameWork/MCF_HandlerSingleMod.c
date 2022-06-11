class MCF_HandlerSingleMod : ScriptedWidgetComponent
{
	
	//todo make layout for single mod settings
	static const string MOD_SETTINGS_LAYOUT_PATH = "{1D2D036656276994}UI/layouts/Menus/SettingsMenu/ModSettings.layout";
	static const string MOD_SINGLE_SETTING_LAYOUT_PATH = "{271E5986CD528C3B}UI/layouts/WidgetLibrary/EditBox/MCF_EditBox.layout";
	
	ref map<string, string> modVariables;
	ref MCF_SettingsManager settingsManager
	ref Widget parent;
	string modId;
	
	ref array<ref MCF_EditBoxComponent> widgetArray;
	SCR_ButtonBaseComponent resetToDefaultButton;
	void MCF_HandlerSingleMod(string id)
	{
		this.modId = id;

	}


	override bool OnClick(Widget w, int x, int y, int button)
	{		
		
		if (!parent)
			parent = w.GetParent().GetParent().GetParent();		//ew

		
		
		VerticalLayoutWidget descriptionLayout = VerticalLayoutWidget.Cast(parent.FindAnyWidget("Description"));
		//Print(TextWidget.Cast(w.FindAnyWidget("TextMod")).GetText());
		
		Widget oldWidget = descriptionLayout.GetChildren();
		
		
		if (oldWidget)
			descriptionLayout.RemoveChild(oldWidget);
		
		

		Widget singleModMenu = GetGame().GetWorkspace().CreateWidgets(MOD_SETTINGS_LAYOUT_PATH, descriptionLayout);
		TextWidget modLabel = TextWidget.Cast(singleModMenu.FindAnyWidget("ModLabel"));
		TextWidget oldTextWidget = TextWidget.Cast(w.FindAnyWidget("TextMod"));
		string oldText = oldTextWidget.GetText();
		modLabel.SetText(oldText);
		
		
		//setup reset to default button 
		ButtonWidget resetToDefaultWidget = ButtonWidget.Cast(singleModMenu.FindAnyWidget("ReturnToDefaultButton"));
		resetToDefaultButton = SCR_ButtonBaseComponent.Cast(resetToDefaultWidget.FindHandler(SCR_ButtonBaseComponent));
		resetToDefaultButton.m_OnClicked.Insert(ResetDefaultValues);
		
		

		
		VerticalLayoutWidget settingsLayout = VerticalLayoutWidget.Cast(singleModMenu.FindAnyWidget("SettingsLayout"));
		
		
		
		
		settingsManager = MCF_SettingsManager.GetInstance();
		modVariables = settingsManager.GetModSettings(modId);	
		
		MCF_JsonManager jsonManager = settingsManager.GetJsonManager(modId);
		//Print(modVariables);
		
		if (!jsonManager)
			return false;
		
		if (modVariables.Count() <= 0)
			Print("Mod Variables is 0");
		
		
		map<string,string> userFriendlyNames = jsonManager.GetUserFriendlyVariableNames();
		array<string> orderArray = jsonManager.GetOrderArray();
		widgetArray = new array<ref MCF_EditBoxComponent>;

		
		
		foreach(string varName : orderArray)
		{
			Widget tempWidget  = GetGame().GetWorkspace().CreateWidgets(MOD_SINGLE_SETTING_LAYOUT_PATH, settingsLayout);
			MCF_EditBoxComponent editBoxComponent = MCF_EditBoxComponent.Cast(tempWidget.FindHandler(MCF_EditBoxComponent));
			widgetArray.Insert(editBoxComponent);
			
			
			editBoxComponent.SetSetting(userFriendlyNames.Get(varName), modVariables.Get(varName));
			editBoxComponent.SetCurrentJsonManager(jsonManager);

		
		}
		

		return true;
		
	}
	
	
	
	void PopulateSettings()
	{
		// Search for correct json 

		
		
	}
	
	void ResetDefaultValues()
	{
		MCF_JsonManager jsonManager = settingsManager.GetJsonManager(modId);
		
		jsonManager.ResetDefaultValues();
		OnClick(parent, 0, 0, 0);			//Just to refresh stuff. not ideal but it works

		
		Print("Will reset everything to default");
		resetToDefaultButton.m_OnClicked.Remove(ResetDefaultValues);
	
	}
	
	
	void ApplyChanges()
	{
		
		//when we apply a setting, we need to reload the mod... or not? 
		// no we don't need to reload anything if it's loaded directly from a json... but probably it'll be slower I guess?
		// we'd probably need some kind of interface to load json ONCE at apply time and then forget about them at runtime 
		
		
		// We'll make a callback to something connected to every compatible mod. That callback will start a re-read of changed values in the json
		
	}
	
	

}



