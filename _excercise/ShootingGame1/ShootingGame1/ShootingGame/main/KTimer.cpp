#include "KTimer.h"

float g_fSecondPerFrame = 0.0f;
bool     KTimer::Init()
{
	m_fSecondPerFrame = 0.0f;
	m_iFPS = 0;
	m_dwFrameCounter = 0;
	m_fAccumulation = 0.0f;
	m_fFrameTime = 0.0f;
	m_dwBeforeTick = timeGetTime();
	return true;
}; // �ʱ�ȭ
   //__imp__timeGetTime@0 �ܺ� ��ȣ(���� ��ġ : "publi
   //winmm.lib
bool     KTimer::Frame() {
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecondPerFrame = dwElapseTick / 1000.0f;
	g_fSecondPerFrame = m_fSecondPerFrame;
	m_fAccumulation += m_fSecondPerFrame;
	m_fFrameTime += m_fSecondPerFrame;
	// FPS
	if (m_fFrameTime >= 1.0f)
	{
		m_iFPS = m_dwFrameCounter;
		m_fFrameTime -= 1.0f;
		m_dwFrameCounter = 0;
	}
	m_dwFrameCounter++;
	m_dwBeforeTick = dwCurrentTick;
	return true;
};
bool     KTimer::Render() {
#ifdef _DEBUG
	static float fTime = 0.0f;
	fTime += m_fSecondPerFrame;
	if (fTime >= 1.0f)
	{
		_stprintf_s(m_csBuffer,
			L"FPS=[%d] %10.4f %10.4f",
			m_iFPS, m_fSecondPerFrame, m_fAccumulation);
		OutputDebugString(m_csBuffer);
		fTime = 0.0f;
	}

#endif
	return true;
};
bool     KTimer::Release() {
	return true;
};


KTimer::KTimer()
{
}


KTimer::~KTimer()
{
}
