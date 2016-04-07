#include "KCore.h"

bool     KCore::Init()
{
	return true;
}; // 초기화
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
		//메세지 큐에서 메세지 1개를 가져온다.
		//메세지는 편집되지 못한 원시 정보.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// 키 해석
			TranslateMessage(&msg);

			//가공된 메세지를 프로시져에 전달.
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
