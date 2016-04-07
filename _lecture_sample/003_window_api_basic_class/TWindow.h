#pragma once
#include <windows.h>
#include <tchar.h>
class TWindow
{
public:
	HWND m_hWnd;
	RECT m_rtWindow;
	RECT m_rtClient;
public:
	bool SetWindow( HINSTANCE hInstatnce,
		TCHAR* titleName = L"Sample Project",
		int iX=0, int iY=0, int iWidth=800,
		int iHeight=600);
public:
	TWindow();
	virtual ~TWindow();
};

