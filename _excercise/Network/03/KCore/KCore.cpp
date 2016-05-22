#include "KCore.h"
HDC		g_hScreenDC;
HDC		g_hOffScreenDC;
bool KCore::GameInit()
{
	m_Timer.Init();
	m_Input.Init();
	// 제 1의 버퍼 전면버퍼
	m_hScreenDC = GetDC(m_hWnd);
	// 제 2의 버퍼를 생성한다.
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);// 메모리
	m_hOffScreenBitmap = CreateCompatibleBitmap(
		m_hScreenDC,
		m_rtWindow.right, 
		m_rtWindow.bottom );
	// 반환값 = 이전 선택되어 있던 비트맵
	m_hOldBitmap = (HBITMAP)SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);
	
	g_hScreenDC = m_hScreenDC;
	g_hOffScreenDC = m_hOffScreenDC;

	// m_hOffScreenDC 를 지운다.
	COLORREF bkColor = RGB(255, 255, 255);
	m_hbrBack = CreateSolidBrush(bkColor);
	m_hbrOld = 
		(HBRUSH)SelectObject(m_hOffScreenDC, m_hbrBack);
	// 폰트
	m_fontDefault = CreateFont( 20, 0, 0, FW_BOLD, 
		0,0,0,0,
		HANGEUL_CHARSET, 3,2,1, 
		VARIABLE_PITCH | FF_ROMAN, 
		_T("고딕"));
	m_fontDefaultOld = (HFONT)SelectObject(m_hOffScreenDC, m_fontDefault);
	Init();
	return true;
}
bool KCore::GameRelease()
{
	Release();
	SelectObject(m_hOffScreenDC, m_hbrOld);
	DeleteObject(m_hbrBack);
	SelectObject(m_hOffScreenDC, m_hOldBitmap);
	SelectObject(m_hOffScreenDC, m_fontDefaultOld);
	DeleteObject(m_fontDefault);

	ReleaseDC(m_hWnd, m_hScreenDC);
	m_Timer.Release();
	m_Input.Release();
	return true;
}
bool KCore::GameFrame()
{
	m_Timer.Frame();
	m_Input.Frame();
	PreFrame();
		Frame();
	PostFrame();
	return true;
}
bool KCore::PreRender()
{
	SelectObject(m_hOffScreenDC, m_hbrBack);
	PatBlt(m_hOffScreenDC, 0, 0,
		m_rtWindow.right, m_rtWindow.bottom,
		PATCOPY);		
	return true;
}
bool KCore::PostRender()
{
	// m_hOffScreenDC 이미지를 m_hScreenDC로 복사해라.
	BitBlt(m_hScreenDC, m_rtWindow.left, m_rtWindow.top,
		m_rtWindow.right, m_rtWindow.bottom,
		m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}
bool KCore::DrawDebug(TCHAR* pString, int iX, int iY)
{	
	if (m_hOffScreenDC != NULL)
	{
		SetBkColor(m_hOffScreenDC, RGB(255, 0, 0));
		SetTextColor(m_hOffScreenDC, RGB(0, 0, 255));
		SetBkMode(m_hOffScreenDC, TRANSPARENT);
		SetTextAlign(m_hOffScreenDC, TA_LEFT);

		TextOut(m_hOffScreenDC, iX, iY, pString, wcslen(pString));
	}
	return true;
}
bool KCore::DrawDebug()
{
	RECT rect;
	if (m_hOffScreenDC != NULL)
	{
		GetClientRect(m_hWnd, &rect);
		SetBkColor(m_hOffScreenDC, RGB(255, 0, 0));
		SetTextColor(m_hOffScreenDC, RGB(0, 0, 255));
		SetBkMode(m_hOffScreenDC, TRANSPARENT);
		// 그리기
		DrawText(m_hOffScreenDC, m_Timer.m_csBuffer, -1,
			&rect, DT_LEFT | DT_VCENTER);	
	}
	return true;
}
bool KCore::GameRender()
{
	PreRender();
		Render();
		m_Timer.Render();	
		m_Input.Render();
		DrawDebug();
	PostRender();
	return true;
}
bool KCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
};
void KCore::MsgEvent(MSG msg)
{
	m_Input.MsgEvent(msg);
};
KCore::KCore()
{
}


KCore::~KCore()
{
}
