modded class EditBoxFilterComponent : ScriptedWidgetComponent
{

	int GetCharacterLimitFilter()
	{
		return m_iCharacterLimit;
	}
	
	
	bool GetPuntuationFilter()
	{
		return m_bPunctuation;
	}
	
	
	bool GetNumbersFilter()
	{
		return m_bNumbers;
	}
	
	bool GetAsciiFilter()
	{
		return m_bASCIIchars;
	}
	
	bool GetUTFMultiByteFilter()
	{
		return m_bUTFMultibyte;
	}
	
	string GetBlacklistFilter()
	{
		return m_sCharBlacklist;
	}
	string GetWhitelistFilter()
	{
		return m_sCharWhitelist;
	}
	
	
	
	void SetCharacterLimitFilter(int val)
	{
		this.m_iCharacterLimit = val;
	}
	
	
	void SetPunctuationFilter(bool val)
	{
		this.m_bPunctuation = val;
	}
	
	void SetNumberFilter(bool val)
	{
		this.m_bNumbers = val;
	}
	
	void SetASCIIFilter(bool val)
	{
		this.m_bASCIIchars = val;
	}
	
	void SetUTFMultiByteFilter(bool val)
	{
		this.m_bUTFMultibyte = val;
	}
	
	void SetBlacklistFilter(string val)
	{

		int blacklistSize = val.Length();
		for (int i = 0; i < blacklistSize; i++)
		{
			int char = m_sCharBlacklist.Get(i).ToAscii();
			m_aBlacklist.Insert(char);
		}

		
	}
	void SetWhitelistFilter(string val)
	{
		int whitelistSize = val.Length();
		for (int i = 0; i < whitelistSize; i++)
		{
			int char = m_sCharWhitelist.Get(i).ToAscii();
			m_aWhitelist.Insert(char);
		}
	}
	
	
	
	
	
	
	

}