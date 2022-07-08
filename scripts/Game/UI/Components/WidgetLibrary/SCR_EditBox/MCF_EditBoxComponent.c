//------------------------------------------------------------------------------------------------
class MCF_EditBoxComponent : SCR_EditBoxComponent 
{

	
	MCF_JsonManager jsonManager;
			
	
	void SetCurrentJsonManager(MCF_JsonManager manager)
	{
		this.jsonManager = manager;
	}
	
	
	void SetSetting(string varName, string varValue, EFilterType type)
	{
		
		SetLabel(varName);		
		SetValue(varValue);
		SetFilter(type);
	}
	
	
	
	
	void SetFilter(EFilterType t)
	{
		//can we actually do this?
		
		EditBoxFilterComponent filter = EditBoxFilterComponent.Cast(m_wEditBox.FindHandler(EditBoxFilterComponent));
		if (filter)
		{
			switch(t)
			{
				case EFilterType.TYPE_BOOL:
				{
					filter.SetCharacterLimitFilter(1);
					filter.SetPunctuationFilter(false);
					filter.SetNumberFilter(false);
					filter.SetASCIIFilter(false);
					filter.SetUTFMultiByteFilter(false);
					//filter.SetWhitelistFilter("ABC123");
					
					
					//TODO ADD BLACKLIST! ONLY 0 AND 1!
					break;
				
				}
				case EFilterType.TYPE_INT:
				{
					filter.SetCharacterLimitFilter(10);
					filter.SetPunctuationFilter(false);
					filter.SetNumberFilter(true);
					filter.SetASCIIFilter(false);
					filter.SetUTFMultiByteFilter(false);
					break;
				}
				case EFilterType.TYPE_FLOAT:
				{
					filter.SetCharacterLimitFilter(10);
					filter.SetPunctuationFilter(true);
					filter.SetNumberFilter(true);
					filter.SetASCIIFilter(false);
					filter.SetUTFMultiByteFilter(false);
					break;
				}
				case EFilterType.TYPE_STRING:
				{
					filter.SetCharacterLimitFilter(15);
					filter.SetPunctuationFilter(true);
					filter.SetNumberFilter(true);
					filter.SetASCIIFilter(true);
					filter.SetUTFMultiByteFilter(true);
					break;
				}
				
			
			}
		
		}

	
	}
	
	
	
	
	
	
	//------------------------------------------------------------------------------------------------
	override protected void OnConfirm(Widget w)
	{
		
		
		
		//VALIDATE INPUT!!!!!!!
		
		
		
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