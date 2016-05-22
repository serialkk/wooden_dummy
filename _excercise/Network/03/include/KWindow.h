#pragma once
#include "KStd.h"


class KWindow
{
public:
	HWND		m_hWnd; // ������ �ڵ�
	HINSTANCE	m_hInstance; // ���ఴü �ڵ�
	RECT		m_rtWindow;
public:
	void	CenterWindow();
	
	bool	SetWindow(HINSTANCE hInstance,
		TCHAR* pTitleName = L"Main",
		int iWidth=800, int iHeight=600,
		DWORD dwStyle = WS_OVERLAPPEDWINDOW);
	bool	Run();
	bool	Release();
	virtual  bool   ResizeClient(UINT iWidth, UINT iHeight);
	virtual  bool	GameRun() { return true; };
	virtual  void   MsgEvent(MSG msg) {};
	virtual  bool	GameInit() { return true; };
	virtual  bool   GameRelease() { return true; };
	virtual LRESULT MsgProc(HWND hWnd,
							UINT msg,
							WPARAM wParam,
							LPARAM lParam);
public:
	KWindow();
	virtual ~KWindow();
};
