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

//운영체제와 메세지 통신하는 함수가 된다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
	WPARAM wParam, //부가적인 정보들
	LPARAM lParam) //부가적인 정보들
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
		//닫기 메세지를 윈도우 프로시져에 등록한다.
		//메세지 큐에 제일 뒤에 WM_QUIT를 추가
		PostQuitMessage(0);
	}
	}

	//나머지 메세지는 운영체제가 알아서 처리해라.
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool KWindow::SetWindow(HINSTANCE hInstance, TCHAR* titleName, int iX, int iY, int iWidth, int iHeight) {
	// 1, 윈도우 클래스 객체 운영체제에 등록
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));


	wc.lpszClassName = L"kgca";
	wc.cbSize = sizeof(WNDCLASSEX); //WNDCLASS 인지 WNDCLASSEX인지 구분하기 위해서
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	// 빌트인( 내장되어 있다. )
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION);
	wc.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

	wc.cbClsExtra = 0;//윈도우 클래스에서 사용하려는 여분의 메모리 크기
	wc.cbWndExtra = 0;//윈도우 에서 사용하려는 여분의 메모리 크기
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

	//2, 등록된 클래스 객체를 사용하여 윈도우 생성
	m_hWnd = CreateWindowEx(
		//작업표시줄 상단에 배치해라.
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
		//3, 윈도우 나타내기, 펼침, 윈도우 뛰우기
		ShowWindow(m_hWnd, SW_SHOW);
	}

	////3, 윈도우 나타내기, 펼침, 윈도띄우기
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
