class MCF_SettingsManager
{
	//Add callback to add a class? 
	
//#define DEBUG_MCF
	
	
	static ref map<string, ref MCF_JsonManager> settingsList;
	
	protected static ref MCF_SettingsManager instance;
	protected static bool toBeInit = true;

	
	/* Will return the current settings list */
	static void Setup(string mod_id, string fileNameJson, OrderedVariablesMap variablesToSet)
	{
		
		if (toBeInit)
		{
			instance = new MCF_SettingsManager();
			settingsList = new map<string, ref MCF_JsonManager>;
			toBeInit = false;
		}
		
		
		MCF_JsonManager mcfJson = new MCF_JsonManager(fileNameJson);
		if (!mcfJson.LoadFromFile(fileNameJson))
			mcfJson.RegisterMap(variablesToSet);
		

		//SHOULD CHECK IF IT'S IN GAME OR LOADING?
		mcfJson.SetUserHelpers(variablesToSet);	
		
		
		if (settingsList.Count() > 0)
		{
			Print("Settings list > 0");
			if (settingsList.Get(mod_id) != null)
			{
				Print("mod present");
			}
			else 
			{
				settingsList.Insert(mod_id, mcfJson);
			}
		
		}
		else 
		{
			Print(" Settings list is empty");
			Print("Inserting " + mod_id);
			Print("Inserting " + mcfJson);
			settingsList.Insert(mod_id, mcfJson);
		
		}

		/*
		// Add the Json manager to the list
		if (settingsList.Count() > 0)
		{
		
			if (settingsList.Get(mod_id) != null)
			{
				Print("NOT NULL!");
				Print(mod_id);
			}
			else
			{
				#ifdef DEBUG_MCF
				Print("Adding " + mod_id + " to MCF");
				#endif
				settingsList.Set(mod_id, mcfJson);
			}
		
		}
		else
		{
			Print("First settings!");
			settingsList.Set(mod_id, mcfJson);
		}
		*/
	}
	
	

	
	static MCF_JsonManager GetJsonManager(string id)
	{
		MCF_JsonManager managerTemp;
		if (settingsList)
		{
			settingsList.Find(id, managerTemp);
			return managerTemp;
		}
		else
			return null;

	}
	

	
	static map<string,string> GetModSettings(string modId)
	{
		
		MCF_JsonManager temp = GetJsonManager(modId);
		
		
		if (!temp)
			return null;
		else
			return temp.GetMapFromJson();

	}
	
	
	static map<string, ref MCF_JsonManager> GetSettingsList()
	{
		return settingsList;
	}	
}












