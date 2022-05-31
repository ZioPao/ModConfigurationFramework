class ModSettingsBase: ModuleGameSettings
{
	[Attribute()]
	
	
	
	// can be inherited, need to be an interface 
	int speed;
	
	
	
	
	
}




class MCF_HandlerSingleMod : ScriptedWidgetComponent
{
	
	
	


	override bool OnClick(Widget w, int x, int y, int button)
	{
		// Should open another dialog menu I guess, or something on the right or whatever. Still, we need to load the specific settings for this mod. 
		
		
		VerticalLayoutWidget descriptionLayout = VerticalLayoutWidget.Cast(w.GetParent().GetParent().GetParent().FindAnyWidget("Description"));
		//Print(TextWidget.Cast(w.FindAnyWidget("TextMod")).GetText());
		
		
		
		
		
		
		//actionRowWidget = GetGame().GetWorkspace().CreateWidgets(MOD_BUTTON_PATH, m_wContentListLayout);

		return true;
		
	}

}



class MCF_ListModMenu : SCR_SettingsSubMenuBase
{


	//ef array<float> variableList;			//loads them as string and then cast them as correct value?
	ref map<string, float> variableList
	ref array<ref SCR_WorkshopItem> enabledAddons;
	
	protected static const string MOD_BUTTON_PATH = "{26E6DFBB569CE75C}UI/layouts/ModButton.layout";
	
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
		Print(enabledAddons);
		
		
		Widget actionRowWidget;

		foreach(SCR_WorkshopItem x : enabledAddons)
		{
			actionRowWidget = GetGame().GetWorkspace().CreateWidgets(MOD_BUTTON_PATH, m_wContentListLayout);
			
			MCF_HandlerSingleMod handler = new MCF_HandlerSingleMod();
			actionRowWidget.AddHandler(handler);
			
			TextWidget textWidget = TextWidget.Cast(actionRowWidget.FindAnyWidget("TextMod"));
			textWidget.SetText(x.GetName());
			
		}

		
	}
	
	
	
	void InitModConfiguration()
	{
		variableList = new map<string, float>;		//will not work I know.
		
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
	
	
	void GetAllEnabledAddons()
	{
		
		enabledAddons = {};

		if (!SCR_AddonManager.GetInstance())
		{
			Print("AddonManager is not initialized");
			return;
		}

		array<ref SCR_WorkshopItem> ret = SCR_AddonManager.GetInstance().GetAllAddons();
		
		foreach (SCR_WorkshopItem x : ret)
		{
			if (x.GetEnabled())
			{	
				enabledAddons.Insert(x);
			}
		}

	
	}




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