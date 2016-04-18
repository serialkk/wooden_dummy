#include "TCore.h"
HDC		g_hScreenDC = NULL;
HDC		g_hOffScreenDC = NULL;

bool     TCore::Init()
{
	return true;
}; // 초기화
bool     TCore::Frame() {
	return true;
};
bool     TCore::Render() {
	return true;
};
bool     TCore::Release() {
	return true;
};
bool TCore::GameInit() {

	m_hScreenDC = GetDC(m_hWnd);
	// 제 2의 버퍼 생성
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(
		m_hScreenDC, 800, 600);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	g_hScreenDC = m_hScreenDC;
	g_hOffScreenDC = m_hOffScreenDC;

	m_Timer.Init();
	m_Input.Init();
	Init();
	return true;
}
bool TCore::GameRun() {
	GameFrame();
	GameRender();
	return true;
}
bool TCore::GameFrame() {
	m_Timer.Frame();
	m_Input.Frame();

	Frame();
	return true;
}
bool TCore::PreRender() {
	// 제 2의 버퍼 초기화, 클리어, 지우기
	COLORREF bkColor = RGB(255, 0, 0);
	HBRUSH  hbrBack = CreateSolidBrush(bkColor);
	HBRUSH old = (HBRUSH)SelectObject(m_hOffScreenDC, hbrBack);
	PatBlt(m_hOffScreenDC, 0, 0, 800, 600,PATCOPY);
	DeleteObject(SelectObject(m_hOffScreenDC, old));
	return true;
}
bool TCore::PostRender() {
	BitBlt(m_hScreenDC, 0, 0, 800, 600,  // 대상 위치
		m_hOffScreenDC, 0, 0, SRCCOPY);//  원본
	return true;
}
bool TCore::GameRender() {	
	PreRender();
		Render();
		m_Timer.Render();
		m_Input.Render();
		DebugString();
	PostRender();
	return true;
}
bool TCore::GameRelease() {

	ReleaseDC(m_hWnd, m_hOffScreenDC);
	ReleaseDC(m_hWnd, m_hScreenDC);

	m_Timer.Release();
	m_Input.Release();
	Release();
	return true;
}
void    TCore::DebugString()
{
	SetBkMode(m_hOffScreenDC, TRANSPARENT);
	TextOut(m_hOffScreenDC,
		0, 0, m_Timer.m_csBuffer,
		_tcslen(m_Timer.m_csBuffer));

	TextOut(m_hOffScreenDC,
		0, 25, m_Input.m_csBuffer,
		_tcslen(m_Input.m_csBuffer));
}
void     TCore::MsgEvent(MSG msg)
{
};
bool TCore::Run()
{
	GameInit();
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		// 메세지 큐에서 메세지 1개를 가져온다.
		// 메세지는 편집되지 못한 원시 정보.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// 키 해석
			TranslateMessage(&msg);
			// 가공된 메세지를 프로시져에 전달.
			DispatchMessage(&msg);

			MsgEvent(msg);
		}
		else {
			//Sleep(10);
			GameRun();
		}
	}
	GameRelease();
	return true;
}


TCore::TCore()
{
}


TCore::~TCore()
{
}
