class VariableInfo
{
	
	string userFriendlyName;
	string variableValue;
	EFilterType type;
	bool show;
	
	string category;
	//int index;
	
	void VariableInfo(string ufn, string vv, EFilterType t = EFilterType.TYPE_STRING, string cat = "", bool showVar = true)
	{
		this.userFriendlyName = ufn;
		this.variableValue = vv;
		this.type = t;
		
		this.category = cat;
		this.show = showVar;
		//this.index = id;
	}

}


class OrderedVariablesMap
{


	ref protected array<string> orderArray;
	
	
	
	ref map<string, ref VariableInfo> variablesInfoMap;
	
	
	
	void OrderedVariablesMap()
	{
		orderArray = new array<string>();
		variablesInfoMap = new map<string, ref VariableInfo>();
	}
	
	void Insert(string variableName, VariableInfo info)
	{
		orderArray.Insert(variableName);
		variablesInfoMap.Insert(variableName, info);	
	}
	
	//awful
	void Set(string variableName, VariableInfo info)
	{
		orderArray.Insert(variableName);
		variablesInfoMap.Insert(variableName, info);	
	}
	
	VariableInfo Get(string key)
	{
		return variablesInfoMap.Get(key);
	
	}
	
	//add remove
	array<string> GetOrderArray()
	{
		return orderArray;
	}
	
	
	map<string, ref VariableInfo> GetMap()
	{
		return variablesInfoMap;
	}

}
