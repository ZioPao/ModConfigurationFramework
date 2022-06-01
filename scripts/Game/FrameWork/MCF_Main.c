class MCF_HandlerSingleMod : ScriptedWidgetComponent
{
	
	//todo make layout for single mod settings
	static const string MOD_SETTINGS_LAYOUT_PATH = "{1D2D036656276994}UI/layouts/Menus/SettingsMenu/ModSettings.layout";
	static const string MOD_SINGLE_SETTING_LAYOUT_PATH = "{271E5986CD528C3B}UI/layouts/WidgetLibrary/EditBox/MCF_EditBox.layout";
	
	ref map<string, string> modVariables;
	
	string modId;
	
	
	void MCF_HandlerSingleMod(string modId)
	{
		this.modId = modId;
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
		
		
		
		
		MCF_SettingsManager manager = MCF_SettingsManager.GetInstance();
		
		
		Print(modId);
		modVariables = manager.GetModSettings(modId);		//ONLY FOR Test;
		Print(modVariables);
		
		
		

		
		
		foreach(string varName, string varValue : modVariables)
		{
			Widget tempWidget  = GetGame().GetWorkspace().CreateWidgets(MOD_SINGLE_SETTING_LAYOUT_PATH, settingsLayout);
			MCF_EditBoxComponent editBoxComponent = MCF_EditBoxComponent.Cast(tempWidget.FindHandler(MCF_EditBoxComponent));
			
			Print(varName);
			Print(varValue);
			Print("__________");
			
			
			editBoxComponent.ReferenceModVariables(modVariables);
			
			editBoxComponent.SetSetting(varName, varValue);
			editBoxComponent.SetCurrentJsonManager(manager.GetJsonManager(modId));

			
		}
		
		
		//VerticalLayoutWidget contentWidget = VerticalLayoutWidget.Cast(singleModMenu.FindAnyWidget("Content"));
		
		
		//VerticalLayoutWidget temp = contentWidget.FindWidget("TitleGeneral");
		
		
		//SCR_CustomLabelComponent currentLabelComponent = SCR_CustomLabelComponent.GetComponent("TitleGeneral", temp, false);
		//currentLabelComponent.SetText(

				
		//labelComponent.GetComponent
		

		


		return true;
		
	}
	
	
	
	void PopulateSettings(string modId)
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







// todo how the fuck do templates works in here
class MCF_JsonManager: JsonApiStruct
{

	protected string settingsFileName;
	
	
	
	ref array<string> keys;
	ref array<string> values;
	ref array<string> types;

		
	void MCF_JsonManager(string fileName)
	{
		settingsFileName = fileName;
		
		keys = new array<string>();
		values = new array<string>();
		types = new array<string>();
		
			
		RegV("keys");
		RegV("values");
		RegV("types");

		if(LoadFromFile(settingsFileName))
			Print("File loaded!");
		else
			Print("Loading failed");

				
	}
	
	
	void RegisterMap(notnull map<string, string> testMap, string type)
	{
		
		foreach (string key, string value : testMap)
		{
			keys.Insert(key);
			values.Insert(value);
			types.Insert(type);
			
		}
		
		PackToFile(settingsFileName)

	}
	
	

	
	map<string, string> GetMapFromJson()
	{
		map<string, string> currentSettings = new map<string, string>();

		
		// todo add some kind of callback to reload map dynamically? 
		for (int i = 0; i < keys.Count(); i++)
			currentSettings.Insert(keys[i], values[i]);


		return currentSettings;

	
	}
	
	void UpdateMap(notnull map<string, string> testMap)
	{
		values = {};		//reset values
		
		
		foreach(string varName, string varValue : testMap)
		{
			values.Insert(varValue);
		}
		
		
			
	}
	
	void SetDefaultValues()
	{
		//you need to override this!
	}
	
	
	string GetFileName()
	{
		return settingsFileName;
	}
	
	
	
	
	///////////////////////////
	override void OnError( int errorCode )
	{
		Print("ERROR CODE " + errorCode.ToString());
		
	}
	
	override void OnSuccess( int errorCode )
	{
		Print("SUCCESS CODE " + errorCode.ToString());
	}
}


























class MCF_ListModMenu : SCR_SettingsSubMenuBase
{


	ref map<string, float> variableList
	ref array< SCR_WorkshopItem> currentlyEnabledAddons;
	
	static const string MOD_BUTTON_PATH = "{26E6DFBB569CE75C}UI/layouts/ModButton.layout";
	
	// Widgets
	protected VerticalLayoutWidget m_wContentListLayout;
	

	override void OnMenuOpen(SCR_SuperMenuBase parentMenu)
	{
		super.OnMenuOpen(parentMenu);
		
		m_wContentListLayout = VerticalLayoutWidget.Cast(GetRootWidget().FindAnyWidget("Content"));
		if (!m_wContentListLayout)
			return;
		
		
		
		m_aSettingsBindings.Clear();
		// bindings must be loaded now. So we must load the mod list here 
		
		
		GetAllEnabledAddons();
		
		
		Widget actionRowWidget;

		foreach(SCR_WorkshopItem item: currentlyEnabledAddons)
		{
			actionRowWidget = GetGame().GetWorkspace().CreateWidgets(MOD_BUTTON_PATH, m_wContentListLayout);
			
			WorkshopItem temp = item.GetWorkshopItem();
			
			MCF_HandlerSingleMod handler = new MCF_HandlerSingleMod(temp.Id());
			actionRowWidget.AddHandler(handler);
			
			TextWidget textWidget = TextWidget.Cast(actionRowWidget.FindAnyWidget("TextMod"));
			textWidget.SetText(temp.Name());
			
		}

		
	}

	
	void GetAllEnabledAddons()
	{
		currentlyEnabledAddons = new array<SCR_WorkshopItem>;

		if (!SCR_AddonManager.GetInstance())
		{
			Print("AddonManager is not initialized");
			return;
		}

		array<ref SCR_WorkshopItem> ret = SCR_AddonManager.GetInstance().GetAllAddons();
		
		foreach (SCR_WorkshopItem item : ret)
		{
			if (item.GetEnabled())
			{					
				currentlyEnabledAddons.Insert(item);
			}
		}

	
	}
	
	
		
	
	/*
	void LoadModConfiguration(string modName, array<string> configSettings)
	{
		
			
			ModSettingsBase settings = GetGame().GetGameUserSettings().GetModule(modName);
		
			
		
		
		
			// Maybe read from a json everything and then load the settings?
		
			foreach(string param : configSettings)
			{
				string tempVar;
				settings.Get(x, tempVar);
			
				if (float.Cast(tempVar))
					variableList.Set(param, float.Cast(tempVar)); 

			
			}
		
		
	}
	
	*/	




}












// DISABLED FOR NOW

/*



// write my settings (ideally in setting menu?)
void ChangeMySettings() 
{
	
	// approach #2
	ModSettingsBase settings = new ModSettingsBase();
	settings.speed = Math.RandomInt(0, 100);
	BaseContainerTools.ReadFromInstance(settings, GetGame().GetGameUserSettings().GetModule(ModSettingsBase));
	
	// notify system about change
	GetGame().UserSettingsChanged(); // -> here is also OnSpeedChanged() called
	GetGame().SaveUserSettings();
}

// register to receive notification about changes
void SomewhereInInit()
{
	GetGame().OnUserSettingsChangedInvoker().Insert(OnSpeedChanged);
}

// read my settings
void OnSpeedChanged() 
{
	// approach #1
	int speed;
	GetGame().GetGameUserSettings().GetModule("MyGameSettings").Get("speed", speed);
	Print("#1 Speed changed = " + speed);
	
	// approach #2
	ModSettingsBase settings = new ModSettingsBase();
	BaseContainerTools.WriteToInstance(settings, GetGame().GetGameUserSettings().GetModule(ModSettingsBase));
	Print("#2 Speed changed = " + settings.speed);	
}


*/