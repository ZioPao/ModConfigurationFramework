class MCF_SettingsManager
{
	//Add callback to add a class? 
	
	
	
	static ref map<string, ref MCF_JsonManager> settingsList;
	protected static ref MCF_SettingsManager instance;
	protected static bool toBeInit = true;
	
	
	
	
	//maybe init somewhere in the game code... Let's init it from BDR for now, but it's to be fixed before going public
	void MCF_SettingsManager()
	{
		Print("SettingsManager initialized");
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
	map<string, string> Setup(string mod_id, string fileNameJson, OrderedVariablesMap variablesToSet)
	{
		MCF_JsonManager mcfJson = new MCF_JsonManager(fileNameJson);
		if (!mcfJson.LoadFromFile(fileNameJson))
			mcfJson.RegisterMap(variablesToSet);
		

		
		mcfJson.SetUserHelpers(variablesToSet);	
		AddJsonManager(mod_id, mcfJson);
		
		
			
		
		
		
		return mcfJson.GetMapFromJson();

	}
	
	
	event void ReloadSettings()
	{
		Print("will reload stuff");
	}
	
	
	
	/*(map<string, string> Setup(string mod_id, string fileNameJson, map<string, string> defaultValues, array<string> userFriendlyVarNames)
	{
	
		MCF_JsonManager mcfJson = new MCF_JsonManager(fileNameJson);

		map<string, string> settings = new map<string, string>;
		
		
		
		
		
		if (!mcfJson.LoadFromFile(fileNameJson))
			mcfJson.RegisterMap(defaultValues);
		
		
		settings = mcfJson.GetMapFromJson();
		mcfJson.SetupUserFriendlyVariableNames(defaultValues, userFriendlyVarNames);
		AddJsonManager(mod_id, mcfJson);
		
		
		return settings;
		
	}
*/
	
	void AddJsonManager(string id, MCF_JsonManager mod)
	{
		
		#ifdef DEBUG_MCF
		Print("Adding " + id + " to MCF");
		#endif
		settingsList.Insert(id, mod);
		
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












