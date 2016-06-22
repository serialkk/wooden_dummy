#include "TTimer.h"

bool TTimer::Init()
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
bool TTimer::Frame()
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

int	TTimer::GetFPS()
{
	return m_iFramePerSecond;
}
float TTimer::GetSPF()
{
	return m_fSecPerFrame;
}

bool TTimer::Render()
{
	return true;
}
bool TTimer::Release()
{
	return true;
}

void TTimer::Reset()
{
	m_bStarted = false;
	m_fEventTime = 0.0f;
	memset(&m_Start, 0, sizeof(LARGE_INTEGER));
	memset(&m_Elapse, 0, sizeof(LARGE_INTEGER));
}

void TTimer::Start()
{
	m_bStarted = true;
	m_fEventTime = 0.0f;
	QueryPerformanceCounter((LARGE_INTEGER *)&m_Start);
}

void TTimer::Stop()
{
	GetElapsedTime();
	m_bStarted = false;
}


bool TTimer::IsStarted() const
{
	return m_bStarted;
}


float TTimer::GetElapsedTime()
{
	if (m_bStarted)
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&m_Elapse);
		m_fEventTime = static_cast<float>(m_Elapse.LowPart - m_Start.LowPart) / static_cast<float>(m_Frequency.LowPart);
	}
	return m_fEventTime;
}

TTimer::TTimer()
{
	m_bStarted = false;
	m_iFramePerSecond = 0;
	m_iFPSElapse = 0;
	m_fSecPerFrame = 0.0f;
	m_fEventTime = 0.0f;

	// �ý����� ���ļ� �������� ��� �´�. �̴� �ð��� ǥ���� ��� ���ؼ� ����Ѵ�.
	QueryPerformanceFrequency((LARGE_INTEGER *)&m_Frequency);
}

TTimer::~TTimer()
{
}