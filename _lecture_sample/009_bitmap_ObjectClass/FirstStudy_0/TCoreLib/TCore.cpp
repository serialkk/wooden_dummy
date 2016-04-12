#include "TCore.h"
bool     TCore::Init()
{
	return true;
}; // �ʱ�ȭ
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
	// �� 2�� ���� ����
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(
		m_hScreenDC, 800, 600);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);


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
	// �� 2�� ���� �ʱ�ȭ, Ŭ����, �����
	COLORREF bkColor = RGB(255, 0, 0);
	HBRUSH  hbrBack = CreateSolidBrush(bkColor);
	SelectObject(m_hOffScreenDC, hbrBack);
	PatBlt(m_hOffScreenDC, 0, 0, 800, 600,
		PATCOPY);	
	return true;
}
bool TCore::PostRender() {
	BitBlt(m_hScreenDC, 0, 0, 800, 600,  // ��� ��ġ
		m_hOffScreenDC, 0, 0, SRCCOPY);//  ����
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
		// �޼��� ť���� �޼��� 1���� �����´�.
		// �޼����� �������� ���� ���� ����.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Ű �ؼ�
			TranslateMessage(&msg);
			// ������ �޼����� ���ν����� ����.
			DispatchMessage(&msg);

			MsgEvent(msg);
		}
		else {
			//Sleep(1);
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
