#include "TShape.h"
#include "TBitmapMgr.h"
#include "TSys.h"

bool TShape::Load( TCHAR* pColor, TCHAR* pMask)
{
	m_pColor = I_BitmapMgr.Load(pColor);
	m_pMask = I_BitmapMgr.Load(pMask);
}
bool TShape::Init()
{
	return true;
}
bool TShape::Frame()
{
	return true;
}
bool TShape::Release()
{
	return true;
}
bool TShape::Render()
{
	BitBlt(g_hOffScreenDC,
		m_Position.x,
		m_Position.y,
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_pMask->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top, SRCAND);

	BitBlt(g_hOffScreenDC, m_Position.x,
		m_Position.y,
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_pColor->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top, SRCINVERT);

	BitBlt(g_hOffScreenDC, m_Position.x,
		m_Position.y,
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_pMask->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top, SRCINVERT);
}
TShape::TShape()
{
}


TShape::~TShape()
{
}
