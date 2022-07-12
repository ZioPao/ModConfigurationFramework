class MCF_SettingsManager
{
	//Add callback to add a class? 
	
#define DEBUG_MCF
	
	
	static ref map<string, ref MCF_JsonManager> settingsList;
	protected static ref MCF_SettingsManager instance;
	protected static bool toBeInit = true;
	
	
	
	void MCF_SettingsManager()
	{
		Print("SettingsManager initialized");
	}
	
	
	void ~MCF_SettingsManager()
	{
		//should relase the json... I guess? 
		//settingsList.Clear();
	
	}
	static MCF_SettingsManager GetInstance()
	{	
		
		if (toBeInit)
		{
			instance = new MCF_SettingsManager();
			settingsList = new map<string, ref MCF_JsonManager>;
			toBeInit = false;
		}
		
		return instance;
	}
	
	static bool IsInitialized()
	{
		return !toBeInit;		
	}
	
	/* Will return the current settings list */
	void Setup(string mod_id, string fileNameJson, OrderedVariablesMap variablesToSet)
	{
		MCF_JsonManager mcfJson = new MCF_JsonManager(fileNameJson);
		if (!mcfJson.LoadFromFile(fileNameJson))
			mcfJson.RegisterMap(variablesToSet);
		

		//SHOULD CHECK IF IT'S IN GAME OR LOADING?
		mcfJson.SetUserHelpers(variablesToSet);	
		
		// in game
		#ifndef WORKBENCH
		AddJsonManager(mod_id, mcfJson);
		#endif
		

	}
	
	
	
	void AddJsonManager(string id, MCF_JsonManager mod)
	{
		
		if (settingsList.Count() > 0)
		{
		
			if (settingsList.Get(id) != null)
			{
				Print("NOT NULL!");
				Print(id);
			}
			else
			{
				#ifdef DEBUG_MCF
				Print("Adding " + id + " to MCF");
				#endif
				settingsList.Set(id, mod);
			}
		
		}
		else
		{
			Print("First settings!");
			settingsList.Set(id,mod);
		}

		
	}
	
	MCF_JsonManager GetJsonManager(string id)
	{
		MCF_JsonManager managerTemp;
		settingsList.Find(id, managerTemp);
		
		return managerTemp;
	}
	

	
	map<string,string> GetModSettings(string modId)
	{
		
		MCF_JsonManager temp = GetJsonManager(modId);
		
		
		if (!temp)
			return null;
		else
			return temp.GetMapFromJson();

	}
	
	
	map<string, ref MCF_JsonManager> GetSettingsList()
	{
		return settingsList;
	}	
}












