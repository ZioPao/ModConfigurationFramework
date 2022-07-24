class MCF_SettingsManager
{
	//Add callback to add a class? 
	
//#define DEBUG_MCF
	
	
	static ref map<string, ref MCF_JsonManager> settingsList;
	
	protected static bool toBeInit = true;

	
	/* Will return the current settings list */
	static void Setup(string mod_id, string fileNameJson, OrderedVariablesMap variablesToSet)
	{
		
		if (toBeInit)
		{
			settingsList = new map<string, ref MCF_JsonManager>;
			toBeInit = false;
		}
		
		
		MCF_JsonManager mcfJson = new MCF_JsonManager(fileNameJson);
		mcfJson.SetUserHelpers(variablesToSet);	
		
		
		#ifndef WORKBENCH
		if (!mcfJson.LoadFromFile(fileNameJson))
			mcfJson.RegisterMap(variablesToSet);
		#else 
		mcfJson.RegisterMap(variablesToSet);
		mcfJson.ResetDefaultValues();		//to make it functional in the workbench
		#endif 	
		

		
		if (settingsList.Count() > 0)
		{
			if (settingsList.Get(mod_id) == null)
				settingsList.Insert(mod_id, mcfJson);

		}
		else 
			settingsList.Insert(mod_id, mcfJson);
		
		


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












