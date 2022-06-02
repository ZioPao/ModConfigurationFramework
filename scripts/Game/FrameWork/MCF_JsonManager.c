/* MCF_JsonManager must be allocated for EACH mod. It's basically the container for your settings*/
class MCF_JsonManager: JsonApiStruct
{

	
	
	
	protected string settingsFileName;
	protected ref map<string, string> userFriendlyKeys;

	
	
	ref array<string> keys;
	ref array<string> values;

		
	void MCF_JsonManager(string fileName)
	{
		settingsFileName = fileName;
		
		keys = new array<string>();
		userFriendlyKeys = new map<string, string>();
		values = new array<string>();
		
			
		RegV("keys");
		RegV("values");

		if(LoadFromFile(settingsFileName))
			Print("File loaded!");
		else
			Print("Loading failed");

				
	}
	
	
	void RegisterMap(notnull map<string, string> testMap)
	{
		
		foreach (string key, string value : testMap)
		{
			keys.Insert(key);
			values.Insert(value);
			
		}
		
		PackToFile(settingsFileName)

	}
	
	void AddReferenceToUserFriendlyVariableNames(map<string, string> userFriendlyStrings)
	{
		userFriendlyKeys = userFriendlyStrings;
		
	}
	
	
	map<string, string> GetUserFriendlyVariableNames()
	{
		return userFriendlyKeys;
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
	

	string GetFileName()
	{
		return settingsFileName;
	}
	
	
	
	
	
	
	/////////////////////////////////////////////////
	// PUBLIC METHODS
	////////////////////////////////////////////////
	
	
	void SetupUserFriendlyVariableNames(map<string, string> originalMapVariables, array<string> ufKeys)
	{
		
		if (!(originalMapVariables.Count() == ufKeys.Count()))
			return;
		
		if (!userFriendlyKeys)
			userFriendlyKeys = new map<string, string>;
		

		map<string, string> tempMap = new map<string, string>;
		for(int i = 0; i < ufKeys.Count(); i++)
			userFriendlyKeys.Insert(originalMapVariables.GetKey(i), ufKeys[i]);
		
		
		
		
		
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