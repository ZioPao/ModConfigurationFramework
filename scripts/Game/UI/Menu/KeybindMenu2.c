class TestKeybindMenu : DialogUI
{
	protected static ref InputBinding s_Binding;
	protected SCR_KeybindSetting m_KeybindMenuComponent;

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		super.OnMenuUpdate(tDelta);
		if (!s_Binding)
			return;

		if (s_Binding.GetCaptureState() == EInputBindingCaptureState.IDLE)
		{
			s_Binding.Save();
			m_KeybindMenuComponent.ListActionsFromCurrentCategory();
			CloseAnimated();
		}
	}

	//------------------------------------------------------------------------------------------------
	override protected void OnCancel()
	{
		m_OnCancel.Invoke();
		s_Binding.CancelCapture();
		CloseAnimated();
	}

	//------------------------------------------------------------------------------------------------
	void SetKeybind(InputBinding binding, SCR_KeybindSetting keybindMenuComponent)
	{
		m_KeybindMenuComponent = keybindMenuComponent;
		s_Binding = binding;
		GetGame().GetInputManager().AddActionListener("MenuBack", EActionTrigger.DOWN, CancelCapture);
	}

	void CancelCapture()
	{
		s_Binding.CancelCapture();
		m_OnCancel.Invoke();
		CloseAnimated();
	}
};
