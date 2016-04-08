#include "TBitmap.h"
#include "TSys.h"
bool     TBitmap::Load(HDC hScreenDC, TCHAR* pFileName)
{
	m_hScreenDC = hScreenDC;
	BITMAP info;
	//HANDLE'에서 'HBITMAP'(으)로 변환할 수 없습니다.
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance,
		pFileName, IMAGE_BITMAP, 0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &info);
	// 메모리 DC 할당( 화면 DC와 호환가능한 제 2의 DC 생성)
	m_hMemDC = CreateCompatibleDC(hScreenDC);
	// 메모리 DC에 비트맵을 적용
	SelectObject(m_hMemDC, m_hBitmap);
	return true;
}

TBitmap::TBitmap()
{
}


TBitmap::~TBitmap()
{
}
