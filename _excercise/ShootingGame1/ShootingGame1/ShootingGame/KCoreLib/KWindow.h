#pragma once
#include "KStd.h"

class KWindow
{
public:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	RECT m_rKWindow;
	RECT m_rtClient;
	int  m_iWidth;
	int  m_iHeight;
public:
	void SetRect(int iWidth, int iHeight);
	bool SetWindow( HINSTANCE hInstatnce,
		TCHAR* titleName = L"Sample Project",
		int iX=0, int iY=0, int iWidth=800,
		int iHeight=600);
	void CenterWindow();
public:
	KWindow();
	virtual ~KWindow();
};

