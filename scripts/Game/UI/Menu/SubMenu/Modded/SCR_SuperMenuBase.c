modded class SCR_SuperMenuBase: ChimeraMenuBase
{
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		super.OnMenuUpdate(tDelta);
		
		if (m_OpenedSubmenu && m_OpenedSubmenu.GetRootWidget().IsVisible())
			m_OpenedSubmenu.OnMenuUpdate(this, tDelta);
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
		// Find tabViewComponent, listen to OnChange
		Widget w = GetRootWidget();
		Widget tab = w.FindAnyWidget(TAB_VIEW_NAME);
		if (!tab)
			return;
		
		m_wFooterLeft = w.FindAnyWidget(FOOTER_LEFT_NAME);
		m_wFooterRight = w.FindAnyWidget(FOOTER_RIGHT_NAME);

		m_TabViewComponent = SCR_TabViewComponent.Cast(tab.FindHandler(SCR_TabViewComponent));
		if (!m_TabViewComponent)
			return;

		m_TabViewComponent.m_OnContentCreate.Insert(OnTabCreate);
		m_TabViewComponent.m_OnContentShow.Insert(OnTabShow);
		m_TabViewComponent.m_OnContentHide.Insert(OnTabHide);
		m_TabViewComponent.m_OnContentRemove.Insert(OnTabRemove);
		
		m_TabViewComponent.Init();

		w.SetOpacity(0);
		WidgetAnimator.PlayAnimation(w,WidgetAnimationType.Opacity,1,WidgetAnimator.FADE_RATE_SUPER_FAST);
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuShow()
	{
		if (m_OpenedSubmenu)
			m_OpenedSubmenu.OnMenuShow(this);
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuHide()
	{
		if (m_OpenedSubmenu)
			m_OpenedSubmenu.OnMenuHide(this);
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuClose()
	{
		foreach (SCR_SubMenuBase subMenu : m_aSubMenus)
		{
			if (subMenu)
				subMenu.OnMenuClose(this);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnTabCreate(SCR_TabViewComponent comp, Widget w)
	{
		if (!w)
			return;
		
		SCR_SubMenuBase subMenu = SCR_SubMenuBase.Cast(w.FindHandler(SCR_SubMenuBase));
		if (!subMenu)
			return;
		
		subMenu.OnMenuOpen(this);
		m_aSubMenus.Insert(subMenu);
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnTabShow(SCR_TabViewComponent comp, Widget w)
	{
		if (!w)
			return;
		
		SCR_SubMenuBase subMenu = SCR_SubMenuBase.Cast(w.FindHandler(SCR_SubMenuBase));
		if (!subMenu)
			return;
		
		subMenu.OnMenuShow(this);
		m_OpenedSubmenu = subMenu;
	}

	//------------------------------------------------------------------------------------------------
	override void OnTabHide(SCR_TabViewComponent comp, Widget w)
	{
		if (!w)
			return;
		
		SCR_SubMenuBase subMenu = SCR_SubMenuBase.Cast(w.FindHandler(SCR_SubMenuBase));
		if (!subMenu)
			return;
		
		subMenu.OnMenuHide(this);
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnTabRemove(SCR_TabViewComponent comp, Widget w)
	{
		if (!w)
			return;
		
		SCR_SubMenuBase subMenu = SCR_SubMenuBase.Cast(w.FindHandler(SCR_SubMenuBase));
		if (!subMenu)
			return;
		
		subMenu.OnMenuClose(this);
		m_aSubMenus.RemoveItem(subMenu);
	}

	//------------------------------------------------------------------------------------------------
	//! rightFooter - when true, the button will be added to the right footer.
	override SCR_NavigationButtonComponent AddNavigationButton(string action, string buttonText, bool rightFooter = false)
	{
		if (!m_wFooterLeft || !m_wFooterRight || m_sNavigationButtonLayout == string.Empty)
			return null;
		
		Widget footer = m_wFooterLeft;
		if (rightFooter)
		{
			footer = m_wFooterRight;
		}
			
		Widget w = GetGame().GetWorkspace().CreateWidgets(m_sNavigationButtonLayout, footer);
		if (!w)
			return null;
		
		HorizontalLayoutSlot.SetPadding(w, 0, 0, 8, 0);
		
		SCR_NavigationButtonComponent comp = SCR_NavigationButtonComponent.Cast(w.FindHandler(SCR_NavigationButtonComponent));
		if (!comp)
			return null;
		
		comp.SetLabel(buttonText);
		comp.SetAction(action);
		return comp;
	}
	
	//------------------------------------------------------------------------------------------------
	override void CloseMenu(bool animate = true)
	{
		if (!animate)
		{
			Close();
			return;
		}
		
		WidgetAnimator.PlayAnimation(GetRootWidget(),WidgetAnimationType.Opacity,0,WidgetAnimator.FADE_RATE_FAST);
		float time = 1 / WidgetAnimator.FADE_RATE_FAST;
		GetGame().GetCallqueue().CallLater(Close, time);
	}
	
	//------------------------------------------------------------------------------------------------
	override void SetTitle(string title)
	{
		TextWidget wTitle = TextWidget.Cast(GetRootWidget().FindAnyWidget(TITLE_NAME));
		if (wTitle)
			wTitle.SetText(title);
	}
};