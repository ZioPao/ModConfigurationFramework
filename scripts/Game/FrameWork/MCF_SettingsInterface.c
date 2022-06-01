class MCF_SettingsManager
{
	//Add callback to add a class? 
	
	static ref map<string, MCF_JsonManager> settingsList;
	protected static ref MCF_SettingsManager instance;
	protected static bool toBeInit = true;
	
	
	string varTest;
	
	
	
	
	//maybe init somewhere in the game code... Let's init it from BDR for now, but it's to be fixed before going public
	
	
	void MCF_SettingsManager()
	{
		Print("SettingsManager initialized");
		varTest = "initialized";
	}
	
	
	
	static MCF_SettingsManager GetInstance()
	{	
		
		if (toBeInit)
		{
			instance = new MCF_SettingsManager();
			settingsList = new map<string, MCF_JsonManager>;
			toBeInit = false;
		}
		
		return instance;
	}
	

	
	void AddJsonManager(string id, MCF_JsonManager mod)
	{
		Print("Adding stuff to MCF");
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
			return new map<string, string>();
		else
			return temp.GetMapFromJson();

	}	
}












