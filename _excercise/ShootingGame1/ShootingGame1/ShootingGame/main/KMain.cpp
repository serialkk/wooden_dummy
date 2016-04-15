#include <windows.h>
#include <tchar.h>
#include "KMain.h"


void     KMain::MsgEvent(MSG msg)
{
	m_Input.MsgEvent(msg);
};
bool KMain::Init()
{
	m_Timer.Init();
	m_Input.Init();
	return true;
}
bool KMain::Frame()
{
	m_Timer.Frame();
	m_Input.Frame();

	if (m_Input.KeyCheck('W') == KEY_PUSH)
	{
		MessageBox(m_hWnd, L"W KEY_UP", L"KeyState", MB_OK);
	}
	if (m_Input.KeyCheck('S') == KEY_PUSH)
	{
		MessageBox(m_hWnd, L"S click", L"KeyState", MB_OK);
	}
	if (m_Input.KeyCheck('A') == KEY_PUSH)
	{
		MessageBox(m_hWnd, L"A click", L"KeyState", MB_OK);
	}
	if (m_Input.KeyCheck('D') == KEY_PUSH)
	{
		MessageBox(m_hWnd, L"D click", L"KeyState", MB_OK);
	}
	return true;
}
bool KMain::Render()
{
	m_Timer.Render();
	m_Input.Render();
	HDC hdc = GetDC(this->m_hWnd);
	//SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 0, 0, m_Timer.m_csBuffer,
		_tcslen(m_Timer.m_csBuffer));
	TextOut(hdc, 0, 25, m_Input.m_csBuffer,
		_tcslen(m_Input.m_csBuffer));
	ReleaseDC(m_hWnd, hdc);
	return true;
}
bool KMain::Release()
{
	m_Timer.Release();
	m_Input.Release();
	return true;
}

int WINAPI wWinMain(
	HINSTANCE hInstatnce,
	HINSTANCE hPrevInstatnce,
	LPWSTR   lpCmdLine,
	int      nCmdShow)
{
	KMain win;
	//win.SetRect(1024, 768);
	if (win.SetWindow(hInstatnce) == true)
	{
		win.Run();
	}
	return 0;
}


KMain::KMain() {}
KMain::~KMain() {}