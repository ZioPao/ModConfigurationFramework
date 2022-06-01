//------------------------------------------------------------------------------------------------
class MCF_EditBoxComponent : SCR_EditBoxComponent 
{

	
	MCF_JsonManager jsonManager;
		
	
	map<string, string> m_variables;
	
	
	void SetCurrentJsonManager(MCF_JsonManager manager)
	{
		this.jsonManager = manager;
	}
	
	
	void SetSetting(string varName, string varValue)
	{
		
		SetLabel(varName);		
		SetValue(varValue);
	}
	
	
	void ReferenceModVariables(map<string, string> variables)
	{
		this.m_variables = variables;
	}
	
	//------------------------------------------------------------------------------------------------
	override protected void OnConfirm(Widget w)
	{
		if (m_bIsTyping)
			m_OnConfirm.Invoke(this, GetValue());
		
		
		
		Print("SAVED VALUE RIGHT NOW!!!");

		
		string currentValue = GetValue();
		string currentText = GetLabel().GetText();
		
		
		int index = 0;
		// get index 
		foreach(string tempString : jsonManager.keys)
		{
		
			if (tempString == currentText)
				break;
			
			index++;
		}
		
		
		
		jsonManager.values[index] = currentValue;

		string tempFileName = jsonManager.GetFileName();
		jsonManager.PackToFile(tempFileName);
		
		
	}
	
};