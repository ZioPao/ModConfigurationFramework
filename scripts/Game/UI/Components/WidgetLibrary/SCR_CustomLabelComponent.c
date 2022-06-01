class SCR_CustomLabelComponent : SCR_ScriptedWidgetComponent
{
	[Attribute("Label's text")]
	protected string m_sLabel;

	protected Widget m_wLabelWidget;

	//------------------------------------------------------------------------------------------------
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);

		if (!w)
			return;

		TextWidget labelWidget = TextWidget.Cast(w.FindAnyWidget("Label"));
		if (!labelWidget)
			return;

		labelWidget.SetText(m_sLabel);
	}
	
	
	Widget GetTextWidget()
	{
		return m_wLabelWidget;
	}
	
	
	
	

	//------------------------------------------------------------------------------------------------
	//! Static method to easily find component by providing name and parent.
	//! Searching all children will go through whole hierarchy, instead of immediate chidren
	static SCR_LabelComponent GetComponent(string name, Widget parent, bool searchAllChildren = true)
	{
		return SCR_LabelComponent.Cast(SCR_ScriptedWidgetComponent.GetComponent(SCR_LabelComponent, name, parent, searchAllChildren));
	}
};
