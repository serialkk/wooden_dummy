#include "KEnemy.h"
#include "KSys.h"

bool KEnemy::Frame()
{
	if (m_fPosX < 0)
	{
		m_fDirection[0] *= -1.0f;
		m_fPosX = 0.0f;
	}
	if (m_fPosX > 800)
	{
		m_fDirection[0] *= -1.0f;
		m_fPosX = 800.0f;
	}
	if (m_fPosY < 0)
	{
		m_fDirection[1] *= -1.0f;
		m_fPosY = 0.0f;
	}
	if (m_fPosY > 600)
	{
		m_fDirection[1] *= -1.0f;
		m_fPosY = 600.0f;
	}
	m_fPosX += m_fDirection[0] * m_fSpeed * g_fSecondPerFrame;
	m_fPosY += m_fDirection[1] * m_fSpeed * g_fSecondPerFrame;

	m_rtCollide.x = m_fPosX - (m_rt.w / 2);
	m_rtCollide.y = m_fPosY - (m_rt.h / 2);
	m_rtCollide.w = m_rtCollide.x + m_rt.w;
	m_rtCollide.h = m_rtCollide.y + m_rt.h;
	return true;
}
KEnemy::KEnemy()
{
}


KEnemy::~KEnemy()
{
}
