// todo how the fuck do templates works in here
class MCF_JsonManager: JsonApiStruct
{

	protected string settingsFileName;
	
	
	
	ref array<string> keys;
	ref array<string> userFriendlyKeys;
	ref array<string> values;
	ref array<string> types;

		
	void MCF_JsonManager(string fileName)
	{
		settingsFileName = fileName;
		
		keys = new array<string>();
		userFriendlyKeys = new array<string>();
		values = new array<string>();
		types = new array<string>();
		
			
		RegV("keys");
		RegV("userFriendlyKeys");
		RegV("values");
		RegV("types");

		if(LoadFromFile(settingsFileName))
			Print("File loaded!");
		else
			Print("Loading failed");

				
	}
	
	
	void RegisterMap(notnull map<string, string> testMap, string type)
	{
		
		foreach (string key, string value : testMap)
		{
			keys.Insert(key);
			values.Insert(value);
			types.Insert(type);
			
		}
		
		PackToFile(settingsFileName)

	}
	
	void AddUserFriendlyVariableNames(array<string> userFriendlyStrings)
	{
		userFriendlyKeys = userFriendlyStrings;
		
		PackToFile(settingsFileName);
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