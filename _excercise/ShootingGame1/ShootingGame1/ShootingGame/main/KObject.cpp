#include "KObject.h"
#include "KSys.h"
#include "KBitmapMgr.h"
bool KObject::Draw()
{
	StretchBlt(m_pBitmap->m_hOffScreenDC,
		m_fPosX,
		m_fPosY,
		m_rt.w,
		m_rt.h,
		m_pBitmap->m_hMemDC,
		m_rt.x, m_rt.y,
		m_pBitmap->m_hBitInfo.bmWidth, // 64
		m_pBitmap->m_hBitInfo.bmHeight,//64
				SRCCOPY); 
	return true;
}
void	 KObject::SetRect(int x, int y, int w, int h)
{
	m_rt.x = x;
	m_rt.y = y;
	m_rt.w = w;
	m_rt.h = h;
}
bool     KObject::Load(HDC hScreenDC,
	HDC hOffScreenDC,
	TCHAR* pFileName)
{
	m_pBitmap = I_BimapMgr.Load(pFileName);
	if (m_pBitmap == NULL)
	{
		return false;
	}	
	return true;
}
void KObject::SetSpeed(float fSpeed)
{
	m_fSpeed += fSpeed * g_fSecondPerFrame;
	if (m_fSpeed < 10.0f) m_fSpeed = 10.0f;
}
void KObject::SetPos(int iX, int iY, float fSpeed)
{	
	m_rtCollide.x = iX- ( m_rt.w / 2);
	m_rtCollide.y = iY- (m_rt.h / 2);
	m_rtCollide.w = m_rtCollide.x + m_rt.w;
	m_rtCollide.h = m_rtCollide.y + m_rt.h;

	m_fPosX = iX;
	m_fPosY = iY;
	m_fSpeed = fSpeed;
}
bool KObject::Init()
{	
	return true;
}

bool KObject::Frame()
{
	return true;
}
bool KObject::Render()
{
	if (m_bUsed == true)
	{
		BitBlt(m_pBitmap->m_hOffScreenDC,
			m_fPosX, m_fPosY,
			m_rt.w,
			m_rt.h,
			m_pBitmap->m_hMemDC,
			m_rt.x, m_rt.y, SRCCOPY);///  원본
		/*StretchBlt(m_pBitmap->m_hOffScreenDC, m_fPosX, m_fPosY,
			800,
			600,
			m_pBitmap->m_hMemDC,
			m_pBitmap->m_hBitInfo.bmWidth/2,
			m_pBitmap->m_hBitInfo.bmHeight/2,
			m_pBitmap->m_hBitInfo.bmWidth- m_pBitmap->m_hBitInfo.bmWidth / 2,
			m_pBitmap->m_hBitInfo.bmHeight- m_pBitmap->m_hBitInfo.bmHeight / 2,
			SRCCOPY); ///  원본*/
	}
	return true;
}

bool KObject::Release()
{
	m_pBitmap->Release();
	return true;
}

KObject::KObject()
{
	m_fDirection[0] = 1.0f;
	m_fDirection[1] = 1.0f;
	m_fSpeed = 0.0f;
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_pBitmap = NULL;
	m_bUsed = true;
}


KObject::~KObject()
{
}
