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
		// �޼��� ť���� �޼��� 1���� �����´�.
		// �޼����� �������� ���� ���� ����.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Ű �ؼ�
			TranslateMessage(&msg);
			//������ �޼����� ���ν����� ����.
			DispatchMessage(&msg);
		}
		else
		{
			//�Ʒ� �Լ��� �ʴ� 60 ���� ȣ�� �ȴٸ� 60fps
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