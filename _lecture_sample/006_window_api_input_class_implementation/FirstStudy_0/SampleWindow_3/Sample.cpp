#include "Sample.h"
#include "TSys.h"
bool	 Sample::Init()
{
	m_hScreenDC = GetDC(m_hWnd);
	m_BackGround.Load(m_hScreenDC,L"../../data/bk.bmp");
	m_Hero.Load(m_hScreenDC, L"../../data/Front.bmp");
	return true;
};
bool	 Sample::Frame() {
	if (m_Input.KeyCheck('S') == KEY_HOLD)
	{
		m_iY += g_fSecondPerFrame * 30.0f;
	}
	if (m_Input.KeyCheck('D') == KEY_HOLD)
	{
		m_iX += g_fSecondPerFrame * 30.0f;
	}
	return true;
};
bool	 Sample::Render() {
	BitBlt(m_hScreenDC, 0, 0, 512, 512,  // 대상 위치
		   m_BackGround.m_hMemDC, 0, 0, SRCCOPY);//  원본
	BitBlt(m_hScreenDC, m_iX, m_iY, 128, 128,  // 대상 위치
			m_Hero.m_hMemDC, 0, 0, SRCCOPY);//  원본
	return true;
};
bool	 Sample::Release() {
	ReleaseDC(m_hWnd, m_hScreenDC);
	return true;
};

Sample::Sample()
{
	m_iX = 0;
	m_iY = 0;
}


Sample::~Sample()
{
}
int WINAPI wWinMain(
	HINSTANCE hInstatnce,
	HINSTANCE hPrevInstatnce,
	LPWSTR   lpCmdLine,
	int      nCmdShow)
{
	Sample win;
	if (win.SetWindow(hInstatnce) == true)
	{
		win.Run();
	}
	return 0;
}