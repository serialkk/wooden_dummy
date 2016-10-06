#pragma once
#include "TBasisStd.h"

#define TIME(t, cmd) { t=mx_get_time(); cmd; t=mx_get_time() - t; }
extern double mx_get_time();

class CStopwatch 
{
public:
    CStopwatch() { QueryPerformanceFrequency(&m_liPerFreq); Start(); }
    void Start() { QueryPerformanceCounter(&m_liPerfStart); } 
   
	__int64 Now() const
	{    // Start 가 호출된 후 경과한 밀리초를 리턴
		LARGE_INTEGER liPerfNow;
		QueryPerformanceCounter(&liPerfNow);
		return(((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000)/ m_liPerFreq.QuadPart);
    }
private:
    LARGE_INTEGER m_liPerFreq;    // 초당 계수
    LARGE_INTEGER m_liPerfStart;   // 시작 계수
};

// 스톱워치를 생성한다(기본 값은 현재 시간).
//CStopwatch stopwatch;
// 여기서 코드를 실행한다.
// 지금까지 얼마나 많은 시간이 경과 되었는지 얻는다.
//__int64 qwElapsedTime = stopwatch.Now();

class TTimer : public TSingleton < TTimer >
{
private:
	friend class TSingleton<TTimer>;
private:
	LARGE_INTEGER	m_Frequency;	// 초당 주파수 
	LARGE_INTEGER	m_Current;		// 현재 시간 
	LARGE_INTEGER	m_Frame;		// 이전 프레임의 시간 체크 
	float			m_fSecPerFrame;	// 프레임 경과 시간 

	LARGE_INTEGER	m_FPS;				// FPS 체크 타이머		
	int				m_iFramePerSecond;	// 초당 프레임	
	int				m_iFPSElapse;		// 초당 경과된 프레임 
	

	LARGE_INTEGER	m_Start;		// 이벤트 타이머 시작 시간
	LARGE_INTEGER	m_Elapse;		// 이베트 타이머 경과 시간
	bool			m_bStarted;			// 이벤트 타이머 작동여부
	float			m_fEventTime;
	

public: 
	// 엔진코어에서 사용하는 지원함수
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

	// 경과한 시간에 대한 지원 함수들
	void	Reset();
	void	Start();
	void	Stop();
	bool	IsStarted() const;
	float	GetElapsedTime();

	// FPS
	int				GetFPS();
	float			GetSPF();

protected: 
	TTimer();  
public:
	virtual ~TTimer();
};
#define I_Timer TTimer::GetInstance()