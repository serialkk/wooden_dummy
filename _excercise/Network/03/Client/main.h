#pragma once
#include "KCore.h"
#include "KAsyncSelect.h"
#pragma comment(lib, "KCoreLib.lib")

class CMain : public KCore
{
public:
	KAsyncSelect	m_Network;
	HWND m_hEdit;
	HWND m_hButton;
	HWND m_hList;
public:
	bool			Init();
	bool			Frame();
	bool			Release();
	LRESULT			MsgProc(HWND hWnd,
					UINT msg,
					WPARAM wParam,
					LPARAM lParam);
	void			MsgEvent(MSG msg);
public:
	CMain();
	virtual ~CMain();
};

