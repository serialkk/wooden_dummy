#include "KWindow.h"

//typedef struct tagWNDCLASSEXW {
//UINT        cbSize;
///* Win 3.x */
//UINT        style;
//WNDPROC     lpfnWndProc;
//int         cbClsExtra;
//int         cbWndExtra;
//HINSTANCE   hInstance;
//HICON       hIcon;
//HCURSOR     hCursor;
//HBRUSH      hbrBackground;
//LPCWSTR     lpszMenuName;
//LPCWSTR     lpszClassName;
///* Win 4.0 */
//HICON       hIconSm;
//}

//�ü���� �޼��� ����ϴ� �Լ��� �ȴ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
	WPARAM wParam, //�ΰ����� ������
	LPARAM lParam) //�ΰ����� ������
{
	switch (msg)
	{
	case WM_SIZE:
	{
		if (wParam == SIZE_MINIMIZED)
		{
			INT KKK = 0;
		}
		if (wParam == SIZE_MAXIMIZED)
		{
			INT KKK = 0;
		}
		UINT iWidth = LOWORD(lParam);
		UINT iHeight = HIWORD(lParam);

		//MessageBox(hWnd, L"800, 600",L"WM_SIZE",MB_OK);
		TCHAR strBuffer[MAX_PATH] = { 0, };
		_stprintf_s(strBuffer, L"%ld %ld\n", iWidth, iHeight);
		OutputDebugString(strBuffer);


	}break;
	case WM_DESTROY:
	{
		//�ݱ� �޼����� ������ ���ν����� ����Ѵ�.
		//�޼��� ť�� ���� �ڿ� WM_QUIT�� �߰�
		PostQuitMessage(0);
	}
	}

	//������ �޼����� �ü���� �˾Ƽ� ó���ض�.
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool KWindow::SetWindow(HINSTANCE hInstance, TCHAR* titleName, int iX, int iY, int iWidth, int iHeight) {
	// 1, ������ Ŭ���� ��ü �ü���� ���
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));


	wc.lpszClassName = L"kgca";
	wc.cbSize = sizeof(WNDCLASSEX); //WNDCLASS ���� WNDCLASSEX���� �����ϱ� ���ؼ�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	// ��Ʈ��( ����Ǿ� �ִ�. )
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION);
	wc.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

	wc.cbClsExtra = 0;//������ Ŭ�������� ����Ϸ��� ������ �޸� ũ��
	wc.cbWndExtra = 0;//������ ���� ����Ϸ��� ������ �޸� ũ��
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;

	if (RegisterClassEx(&wc) == false) {
		return false;
	}

	/*CreateWindowExW(
	_In_ DWORD dwExStyle,
	_In_opt_ LPCWSTR lpClassName,
	_In_opt_ LPCWSTR lpWindowName,
	_In_ DWORD dwStyle,
	_In_ int X,
	_In_ int Y,
	_In_ int nWidth,
	_In_ int nHeight,
	_In_opt_ HWND hWndParent,
	_In_opt_ HMENU hMenu,
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ LPVOID lpParam);
	*/

	//2, ��ϵ� Ŭ���� ��ü�� ����Ͽ� ������ ����
	m_hWnd = CreateWindowEx(
		//�۾�ǥ���� ��ܿ� ��ġ�ض�.
		WS_EX_APPWINDOW, //DWORD dwExStyle,
		L"KGCA",
		L"Sample Window",
		WS_OVERLAPPEDWINDOW, //DWORD dwStyle,//WS_POPUPWINDOW,//
		iX,//int X,
		iY,//int Y,
		iWidth,// int nWidth,
		iHeight,// nHeight,
		NULL,//HWND hWndParent,
		NULL,//HMENU hMenu,
		hInstance,//HINSTANCE hInstance,
		NULL//LPVOID lpParam);
		);
	if (m_hWnd != NULL)
	{
		//3, ������ ��Ÿ����, ��ħ, ������ �ٿ��
		ShowWindow(m_hWnd, SW_SHOW);
	}

	////3, ������ ��Ÿ����, ��ħ, ��������
	//ShowWindow(m_hWnd, SW_SHOW);
	RECT m_rtWindow, m_rtWClient;
	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtWClient);

	return true;
}

KWindow::KWindow()
{
}


KWindow::~KWindow()
{
}
