//------------------------------------------------------------------------------------------------
class MCF_EditBoxComponent : SCR_EditBoxComponent 
{

	
	MCF_JsonManager jsonManager;
			
	
	void SetCurrentJsonManager(MCF_JsonManager manager)
	{
		this.jsonManager = manager;
	}
	
	
	void SetSetting(string varName, string varValue)
	{
		
		SetLabel(varName);		
		SetValue(varValue);
	}
	
	
	
	//------------------------------------------------------------------------------------------------
	override protected void OnConfirm(Widget w)
	{
		if (m_bIsTyping)
			m_OnConfirm.Invoke(this, GetValue());

		string currentValue = GetValue();
		string currentText = GetLabel().GetText();
		
		map<string, string> userFriendlyAliases = jsonManager.GetUserFriendlyVariableNames();
				
		
		string currentKey;
		
		foreach(string key, string value : userFriendlyAliases)
		{
			if (value == currentText)
			{
				currentKey = key;
				break;
				
			}
				

		}
		
		
		
		
		
		int index = 0;
		// get index 
		foreach(string tempString : jsonManager.keys)
		{
		
			if (tempString == currentKey)
				break;
			
			index++;
		}
		
		
		
		jsonManager.values[index] = currentValue;

		string tempFileName = jsonManager.GetFileName();
		jsonManager.PackToFile(tempFileName);
		
		Print("MCF: Saved " + currentKey + "=" + currentValue + " to " + tempFileName);
		
		
	}
	
};