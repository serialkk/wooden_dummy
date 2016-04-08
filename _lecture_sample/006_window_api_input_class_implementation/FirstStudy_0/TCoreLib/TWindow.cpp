#include "TWindow.h"
//1>  TCoreLib.vcxproj->D:\MyProjects\FirstStudy
//_0\TCoreLib\..
/// .. / output / TCoreLib\TCoreLib.lib
HWND g_hWnd= NULL;
HINSTANCE g_hInstance;
void TWindow::SetRect(int iWidth, int iHeight)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
}
// 운영체제와 메세지 통신하는 함수가 된다.
LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,// 부가적인 정보들
	LPARAM lParam)// 부가적인 정보들
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
		TCHAR strBuffer[MAX_PATH] = { 0, };
		_stprintf_s(strBuffer, L"%ld %ld\n", iWidth, iHeight);
		OutputDebugString(strBuffer);
		//MessageBox(hWnd, strBuffer, L"WM_SIZE", MB_OK);

	}break;
	case WM_DESTROY:
	{
		// 닫기 메세지를 윈도우 프로시져에 등록한다.
		// 메세지 큐에 제일 뒤에 WM_QUIT 를 추가
		PostQuitMessage(0);
	}
	}
	// 나머지 메세지는 운영체제가 알아서 처리해라.
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
bool TWindow::SetWindow( HINSTANCE hInstatnce,
	TCHAR* titleName,
	int iX, int iY, int iWidth,
	int iHeight)
{
	m_hInstance = hInstatnce;
	g_hInstance = hInstatnce;
	if (m_iWidth == 0 && m_iHeight == 0)
	{
		m_iWidth = iWidth;
		m_iHeight = iHeight;
	}
	// 1, 윈도우 클래스 객체 운영체제에 등록
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.lpszClassName = L"KGCA";
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstatnce;
	// 빌트인( 내장되어 있다. )
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION);
	wc.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.cbClsExtra = 0;// 윈도우 클래스에서 사용하려는 여분의 메모리 크기
	wc.cbWndExtra = 0;// 윈도우에서 사용하려는 여분의 메모리 크기
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	if (RegisterClassEx(&wc) == false)
	{
		return false;
	}

	// 2, 등록된 클래스 객체를 사용하여 윈도우 생성
	m_hWnd = CreateWindowEx(
		// 작업표시줄 상단에 배치해라.
		WS_EX_APPWINDOW, //DWORD dwExStyle,
		L"KGCA",
		titleName,
		WS_OVERLAPPEDWINDOW,//WS_OVERLAPPEDWINDOW, //WS_POPUPWINDOW, //DWORD dwStyle,
		iX, //int X,
		iY,//int Y,
		m_iWidth,//int nWidth,
		m_iHeight,//int nHeight,
		NULL, //HWND hWndParent,
		NULL,//HMENU hMenu,
		hInstatnce,//HINSTANCE hInstance,
		NULL);  //LPVOID lpParam);
	if (m_hWnd != NULL)
	{
		// 3, 윈도우 나타내기, 펼침, 윈도우 뛰우기
		ShowWindow(m_hWnd, SW_SHOW);
	}
	g_hWnd = m_hWnd;

	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);
	return true;
}

TWindow::TWindow()
{
	m_iWidth = 0;
	m_iHeight = 0;
}


TWindow::~TWindow()
{
}
