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
		// �޼��� ť���� �޼��� 1���� �����´�.
		// �޼����� �������� ���� ���� ����.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Ű �ؼ�
			TranslateMessage(&msg);
			// ������ �޼����� ���ν����� ����.
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