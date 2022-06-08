/* MCF_JsonManager must be allocated for EACH mod. It's basically the container for your settings*/
class MCF_JsonManager: JsonApiStruct
{

	
	
	
	protected string settingsFileName;
	protected ref map<string, string> userFriendlyKeys;
	
	
	protected ref map<string, string> currentSettings;		//no idea if it'll work
	
	
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
	
	
	
	
	
	void RegisterMap(notnull map<string, ref VariableInfo> variablesMap)
	{
		foreach(string key, VariableInfo varInfo : variablesMap)
		{
			keys.Insert(key);
			values.Insert(varInfo.variableValue);
		}
	
		PackToFile(settingsFileName)

	}
	
	
	
	/*
	void RegisterMap(notnull map<string, string> testMap)
	{
		
		foreach (string key, string value : testMap)
		{
			keys.Insert(key);
			values.Insert(value);
			
		}
		
		PackToFile(settingsFileName)

	}
	*/
	
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
		LoadFromFile(settingsFileName);
		
		currentSettings = new map<string, string>();		//reinit 
		
		
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
	
	#define DEBUG_MCF
	
	
	
	
	
	void SetupUserFriendlyVariableNames(map<string, ref VariableInfo> variableMap)
	{
		if (!userFriendlyKeys)
			userFriendlyKeys = new map<string, string>;
		
		map<string, string> tempMap = new map<string, string>;
		foreach(string variableName, VariableInfo varInfo : variableMap)
			userFriendlyKeys.Insert(variableName, varInfo.userFriendlyName);

	
	}
	
	
	
	/*
	void SetupUserFriendlyVariableNames(map<string, string> originalMapVariables, array<string> ufKeys)
	{
		
		if (!(originalMapVariables.Count() == ufKeys.Count()))
			return;
		
		if (!userFriendlyKeys)
			userFriendlyKeys = new map<string, string>;
		

		map<string, string> tempMap = new map<string, string>;
		for(int i = 0; i < ufKeys.Count(); i++)
			userFriendlyKeys.Insert(originalMapVariables.GetKey(i), ufKeys[i]);
		
		
		#ifdef DEBUG_MCF
		
		foreach(string originalVarName, string friendlyVarName : userFriendlyKeys)
		{
			Print(originalVarName);
			Print(friendlyVarName);
			Print("_________________________");
		}
		#endif
		
		
	}
	*/
	
	
	
	
	//todo this should be called after we get a change. The user should override the json manager then to reset everything in here? 
	//we really need to think this thorugh 
	void ReloadSettings()
	{
	
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