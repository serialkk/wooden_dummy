#pragma once

#include "KStd.h"
class KWindow
{
public:
	HWND m_hWnd;

public: 
	bool SetWindow(HINSTANCE hInstance,
		TCHAR* titleName = L"Sample Project",
		int iX=0, int iY=0, int iWidth=800,int iHeight=600);

public:
	KWindow();
	virtual ~KWindow();
};

