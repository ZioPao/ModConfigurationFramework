/* MCF_JsonManager must be allocated for EACH mod. It's basically the container for your settings*/
class MCF_JsonManager: JsonApiStruct
{

	
	
	
	protected string settingsFileName;
	protected ref map<string, string> defaultVariables;
	protected ref map<string, string> userFriendlyKeys;
	protected ref array<string> orderArray;
	
	
	protected ref map<string, string> currentSettings;		//no idea if it'll work
	
	
	ref array<string> keys;
	ref array<string> values;

		
	void MCF_JsonManager(string fileName)
	{
		settingsFileName = fileName;
		
		keys = new array<string>();
		userFriendlyKeys = new map<string, string>();
		defaultVariables = new map<string, string>();
		values = new array<string>();
		
			
		RegV("keys");
		RegV("values");

		if(LoadFromFile(settingsFileName))
		{
			#ifdef DEBUG_MCF
			Print("File loaded!");
			#endif
		}
		else
		{
			#ifdef DEBUG_MCF 
			Print("Loading failed");
			#endif
		}

				
	}
	
	
	
	void RegisterMap(notnull OrderedVariablesMap variablesMap)
	{
	
		foreach(string key, VariableInfo varInfo : variablesMap.GetMap())
		{
			keys.Insert(key);
			values.Insert(varInfo.variableValue);
		}
	
		SetOrder(variablesMap);				//Saves the order of the variables
		PackToFile(settingsFileName);
	}
	

	
	// OLD DON"T USE THIS!!!!
	/*void RegisterMap(notnull map<string, ref VariableInfo> variablesMap)
	{
		foreach(string key, VariableInfo varInfo : variablesMap)
		{
			keys.Insert(key);
			values.Insert(varInfo.variableValue);
		}
	

		PackToFile(settingsFileName)

	}
	*/
	
	
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
	
	
	
	
	void SetUserHelpers(OrderedVariablesMap variablesMap)
	{
		if (!userFriendlyKeys)
			userFriendlyKeys = new map<string, string>;
		
		map<string, ref VariableInfo> tempMap = variablesMap.GetMap();
		foreach(string variableName, VariableInfo varInfo : tempMap)
		{
			userFriendlyKeys.Insert(variableName, varInfo.userFriendlyName);
			defaultVariables.Insert(variableName, varInfo.variableValue);

		}
		
		

		SetOrder(variablesMap);
	}
		
	
	void SetOrder(notnull OrderedVariablesMap variablesMap)
	{
	
		this.orderArray = variablesMap.GetOrderArray();
	}
	
	
	
	protected void SetupUserFriendlyVariableNames(OrderedVariablesMap variableMap)
	{
		if (!userFriendlyKeys)
			userFriendlyKeys = new map<string, string>;
		
		map<string, ref VariableInfo> tempMap = variableMap.GetMap();
		foreach(string variableName, VariableInfo varInfo : tempMap)
			userFriendlyKeys.Insert(variableName, varInfo.userFriendlyName);

	
	}
	
	
	void ResetDefaultValues()
	{
		
		keys = {};
		values = {};
		
		
		foreach(string variableName, string variableValue : defaultVariables)
		{
			
			
			keys.Insert(variableName);
			values.Insert(variableValue);
		}
		
		
		
		PackToFile(settingsFileName);

	
	}
	
	
	
	
	array<string> GetOrderArray()
	{
		return orderArray;
	}
	

	
	
	
	
	
	///////////////////////////
	override void OnError( int errorCode )
	{
		//Print("ERROR CODE " + errorCode.ToString());
		
	}
	
	override void OnSuccess( int errorCode )
	{
		//Print("SUCCESS CODE " + errorCode.ToString());
	}
}