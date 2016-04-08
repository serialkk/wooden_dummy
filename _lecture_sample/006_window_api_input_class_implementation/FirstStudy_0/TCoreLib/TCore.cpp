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
bool TCore::GameRender() {
	m_Timer.Render();
	m_Input.Render();

	Render();
	return true;
}
bool TCore::GameRelease() {
	m_Timer.Release();
	m_Input.Release();
	Release();
	return true;
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
