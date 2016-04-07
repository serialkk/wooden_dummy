#include "TWindow.h"

bool GameInit() {
	return true;
}
bool GameRun() {
	return true;
}
bool GameRelease() {
	return true;
}
bool Run()
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
int WINAPI wWinMain(
	HINSTANCE hInstatnce,
	HINSTANCE hPrevInstatnce,
	LPWSTR   lpCmdLine,
	int      nCmdShow )
{
	TWindow win;
	if (win.SetWindow(hInstatnce) == true)
	{
		Run();
	}
	return 0;
}