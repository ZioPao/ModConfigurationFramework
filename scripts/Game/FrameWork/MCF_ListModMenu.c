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
			
			
			ResourceName addonManagerResourceName = "{0EBD16106CC9FFDC}Prefabs/addonManagerPrefab.et";
			Resource addonManagerResource = Resource.Load(addonManagerResourceName);
			
			GetGame().SpawnEntityPrefab(addonManagerResource);
			
			Print("AddonManager is not initialized");
			//return;
		}

		

		map<string, ref MCF_JsonManager> mapCurrentlyActiveMods = MCF_SettingsManager.GetSettingsList();
	
		
		array<ref SCR_WorkshopItem> ret = SCR_AddonManager.GetInstance().GetAllAddons();
		
		foreach (SCR_WorkshopItem item : ret)
		{
			if (item.GetEnabled() && mapCurrentlyActiveMods.Get(item.GetId()))
			{					
				currentlyEnabledAddons.Insert(item);
			}
		}

		
		//we need to find compatible only mods!!
		

	
	}
	
	
		




}



