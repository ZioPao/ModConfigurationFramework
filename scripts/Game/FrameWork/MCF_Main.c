class ModSettingsBase: ModuleGameSettings
{
	[Attribute()]
	
	
	
	// can be inherited, need to be an interface 
	int speed;
	
	
	
	
	
}




class MCF_HandlerSingleMod : ScriptedWidgetComponent
{
	
	//todo make layout for single mod settings
	


	override bool OnClick(Widget w, int x, int y, int button)
	{
		// Should open another dialog menu I guess, or something on the right or whatever. Still, we need to load the specific settings for this mod. 
		
		
		VerticalLayoutWidget descriptionLayout = VerticalLayoutWidget.Cast(w.GetParent().GetParent().GetParent().FindAnyWidget("Description"));
		//Print(TextWidget.Cast(w.FindAnyWidget("TextMod")).GetText());
		
		Widget oldWidget = descriptionLayout.GetChildren();
		
		
		if (oldWidget)
			descriptionLayout.RemoveChild(oldWidget);
		
		

		Widget singleModMenu = GetGame().GetWorkspace().CreateWidgets(MCF_ListModMenu.MOD_BUTTON_PATH, descriptionLayout);
		
		
		TextWidget textWidget = TextWidget.Cast(singleModMenu.FindAnyWidget("TextMod"));
		
		TextWidget oldTextWidget = TextWidget.Cast(w.FindAnyWidget("TextMod"));

		textWidget.SetText(oldTextWidget.GetText());
		
		


		return true;
		
	}
	
	
	void ApplyChanges()
	{
		
		//when we apply a setting, we need to reload the mod... or not? 
		// no we don't need to reload anything if it's loaded directly from a json... but probably it'll be slower I guess?
		// we'd probably need some kind of interface to load json ONCE at apply time and then forget about them at runtime 
		
		
		// We'll make a callback to something connected to every compatible mod. That callback will start a re-read of changed values in the json
		
	}
	
	

}



class MCF_ListModMenu : SCR_SettingsSubMenuBase
{


	//ef array<float> variableList;			//loads them as string and then cast them as correct value?
	ref map<string, float> variableList
	ref array<ref SCR_WorkshopItem> enabledAddons;
	
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