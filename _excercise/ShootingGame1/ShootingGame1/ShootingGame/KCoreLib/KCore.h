#pragma once
#include "KWindow.h"
#include "KTimer.h"
#include "KInput.h"

class KCore : public KWindow
{
public:
	HDC			m_hScreenDC;  // 제 1 DC => 결과
	// 제 2 DC=> 과정
	HDC			m_hOffScreenDC;
	// 제 2 DC의 비트맵
	HBITMAP		m_hOffScreenBitmap;
public :
	KTimer     m_Timer;
	KInput     m_Input;
public:
	virtual bool     Init(); // 초기화
	virtual bool     Frame();// 계산
	virtual bool     PreRender();// 드로우
	virtual bool     Render();// 드로우
	virtual bool     PostRender();// 드로우
	virtual bool     Release();// 삭제, 소멸
	virtual void     DebugString();
	virtual void     MsgEvent(MSG msg);
public:
	bool Run();
	bool GameRun();
	bool GameInit();
	bool GameFrame();
	bool GameRender();
	bool GameRelease();
public:
	KCore();
	virtual ~KCore();
};

