#pragma once
#include "KBase.h"
class KTimer : public KBase
{
public:
	int		 m_iFPS; // 초당 프레임 카운터
	float	 m_fSecondPerFrame;// 시간의 동기화
	float	 m_fAccumulation; // 시작이후에 경과시간.
public:
	TCHAR    m_csBuffer[MAX_PATH];
	DWORD	 m_dwBeforeTick;
	float    m_fFrameTime;
	DWORD	 m_dwFrameCounter;
public:
	bool     Init(); // 초기화
	bool     Frame();// 계산
	bool     Render();// 드로우
	bool     Release();// 삭제, 소멸
public:
	KTimer();
	virtual ~KTimer();
};
