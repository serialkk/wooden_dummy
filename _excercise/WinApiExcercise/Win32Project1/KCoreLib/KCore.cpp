#include "KCore.h"

bool     KCore::Init()
{
	return true;
}; // �ʱ�ȭ
bool     KCore::Frame() {
	return true;
};
bool     KCore::Render() {
	return true;
};
bool     KCore::Release() {
	return true;
};


bool KCore::Run() { 
	GameInit();
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		//�޼��� ť���� �޼��� 1���� �����´�.
		//�޼����� �������� ���� ���� ����.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Ű �ؼ�
			TranslateMessage(&msg);

			//������ �޼����� ���ν����� ����.
			DispatchMessage(&msg);
		}
		else {
			GameRun();
		}
	}
	GameRelease();

	return true; 
}
bool KCore::GameRun() { 
	GameFrame();
	GameRender();
	return true; 
}
bool KCore::GameInit() {
	Init();
	return true;
}
bool KCore::GameFrame() { 
	Frame();
	return true; 
}
bool KCore::GameRender() { 
	Render();
	return true; 
}
bool KCore::GameRelease() { 
	Release();
	return true; 
}


KCore::KCore()
{
}


KCore::~KCore()
{
}
