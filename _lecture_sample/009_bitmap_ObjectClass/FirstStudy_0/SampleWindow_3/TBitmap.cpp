#include "TBitmap.h"
#include "TSys.h"
bool     TBitmap::Load( HDC hScreenDC, 
						HDC hOffScreenDC,
						TCHAR* pFileName)
{
	m_hScreenDC = hScreenDC;
	m_hOffScreenDC = hOffScreenDC;
	//HANDLE'에서 'HBITMAP'(으)로 변환할 수 없습니다.
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance,
		pFileName, IMAGE_BITMAP, 0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_hBitInfo);
	// 메모리 DC 할당( 화면 DC와 호환가능한 제 2의 DC 생성)
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	// 메모리 DC에 비트맵을 적용
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	return true;
}

bool TBitmap::Init()
{
	return true;
}

bool TBitmap::Frame()
{
	return true;
}

bool TBitmap::Render()
{
	BitBlt(m_hOffScreenDC, 0, 0,
		m_hBitInfo.bmWidth,
		m_hBitInfo.bmHeight,		
		m_hMemDC, 0, 0, SRCCOPY);//  원본
	//StretchBlt( m_hOffScreenDC, 
	//			0,
	//			0,
	//			800,
	//			600,		
	//			m_hMemDC, 
	//	100,//m_hBitInfo.bmWidth/2, 
	//	m_hBitInfo.bmHeight/2,
	//			m_hBitInfo.bmWidth,
	//			m_hBitInfo.bmHeight,
	//			SRCCOPY);//  원본
	return true;
}

bool TBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	ReleaseDC(g_hWnd, m_hMemDC);
	return true;
}
TBitmap::TBitmap()
{
}


TBitmap::~TBitmap()
{
}
