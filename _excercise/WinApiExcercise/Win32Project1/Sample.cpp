#include <windows.h>
#include <tchar.h>
#include "KWindow.h"


bool GameInit() {
	return true;
}

bool GameRelease() {
	return true;
}

bool GameRun() {
	return true;
}

bool Run()
{
	GameInit();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));



	while (msg.message != WM_QUIT)
	{
		// 메세지 큐에서 메세지 1개를 가져온다.
		// 메세지는 편집되지 못한 원시 정보.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// 키 해석
			TranslateMessage(&msg);
			//가공된 메세지를 프로시저에 전달.
			DispatchMessage(&msg);
		}
		else
		{
			//아래 함수가 초당 60 번에 호출 된다면 60fps
			GameRun();
		}
	}
	GameRelease();
	return true;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdSHow)
{
	KWindow win;
	if (win.SetWindow(hInstance) == true)
	{
		Run();
	}
	return 0;
}