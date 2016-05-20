#include "TCore.h"
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
	Init();
	return true;
}
bool TCore::GameRun() {
	GameFrame();
	GameRender();
	return true;
}
bool TCore::GameFrame() {
	Frame();
	return true;
}
bool TCore::GameRender() {
	Render();
	return true;
}
bool TCore::GameRelease() {
	Release();
	return true;
}
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
		}
		else {
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
