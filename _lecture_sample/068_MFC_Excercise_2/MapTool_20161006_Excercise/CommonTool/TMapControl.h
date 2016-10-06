#pragma once

#include "TMapForm.h"

// TMapControl

class TMapControl : public CDockablePane
{
	DECLARE_DYNAMIC(TMapControl)

public:
	TMapControl();
	virtual ~TMapControl();

	TMapForm* m_wndForm;

protected:
	DECLARE_MESSAGE_MAP()
public:
	//virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


