#include "KImage.h"
//#include "KCoreSys.h"

bool	KImage::Init()
{
	return true;
}

bool	KImage::Frame(){
	return true;
}
bool	KImage::Render(){
	return true;
}
bool	KImage::Release(){
	SelectObject( m_hMemDC, m_hOldBitmap );
	DeleteObject( m_hBitmap );
	DeleteDC( m_hMemDC );
	return true;
}

bool KImage::Load(	HWND hWnd, 
					HDC hdc,
	T_STR fileName )
{
	m_hMemDC = CreateCompatibleDC( hdc );
	m_hBitmap =(HBITMAP)LoadImage(g_hInstance,
		fileName.c_str(), 
		IMAGE_BITMAP,
		0, 0, 
		LR_DEFAULTSIZE | LR_LOADFROMFILE );

	m_hOldBitmap = (HBITMAP)SelectObject(
				m_hMemDC,
				m_hBitmap );
	return true;
}
KImage::KImage(void)
{
	m_strName = _T("");
}


KImage::~KImage(void)
{
}
