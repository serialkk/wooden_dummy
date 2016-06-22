#include "KTimer.h"

bool KTimer::Init()
{
	QueryPerformanceCounter(&m_Frame);

	// ���ػ� Ÿ�̸� �������� �Ǵ�
	if (m_Frame.QuadPart == 0)
	{
		return false;
	}

	m_FPS = m_Frame;
	m_iFramePerSecond = 0;
	m_iFPSElapse = 0;
	m_fSecPerFrame = 0.0f;

	Start();
	return true;
}
bool KTimer::Frame()
{
	// 1�������� �ð� üũ 
	// ���� �ð��� ã�´�. 
	QueryPerformanceCounter(&m_Current);
	m_fSecPerFrame = static_cast<float>(m_Current.QuadPart - m_Frame.QuadPart) / static_cast<float>(m_Frequency.QuadPart);

	// 1�ʴ� ������ üũ 	
	if (((m_Current.LowPart - m_FPS.LowPart) / m_Frequency.LowPart) >= 1)
	{
		m_iFramePerSecond = m_iFPSElapse;
		m_iFPSElapse = 0;
		m_FPS = m_Current;
	}
	m_iFPSElapse++;

	m_Frame = m_Current;

	return true;
}

int	KTimer::GetFPS()
{
	return m_iFramePerSecond;
}
float KTimer::GetSPF()
{
	return m_fSecPerFrame;
}

bool KTimer::Render()
{
	return true;
}
bool KTimer::Release()
{
	return true;
}

void KTimer::Reset()
{
	m_bStarted = false;
	m_fEventTime = 0.0f;
	memset(&m_Start, 0, sizeof(LARGE_INTEGER));
	memset(&m_Elapse, 0, sizeof(LARGE_INTEGER));
}

void KTimer::Start()
{
	m_bStarted = true;
	m_fEventTime = 0.0f;
	QueryPerformanceCounter((LARGE_INTEGER *)&m_Start);
}

void KTimer::Stop()
{
	GetElapsedTime();
	m_bStarted = false;
}


bool KTimer::IsStarted() const
{
	return m_bStarted;
}


float KTimer::GetElapsedTime()
{
	if (m_bStarted)
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&m_Elapse);
		m_fEventTime = static_cast<float>(m_Elapse.LowPart - m_Start.LowPart) / static_cast<float>(m_Frequency.LowPart);
	}
	return m_fEventTime;
}

KTimer::KTimer()
{
	m_bStarted = false;
	m_iFramePerSecond = 0;
	m_iFPSElapse = 0;
	m_fSecPerFrame = 0.0f;
	m_fEventTime = 0.0f;

	// �ý����� ���ļ� �������� ��� �´�. �̴� �ð��� ǥ���� ��� ���ؼ� ����Ѵ�.
	QueryPerformanceFrequency((LARGE_INTEGER *)&m_Frequency);
}

KTimer::~KTimer()
{
}