#pragma once
#include "TWindow.h"

class TCore : public TWindow
{
public :

public:
	virtual bool     Init(); // 초기화
	virtual bool     Frame();// 계산
	virtual bool     Render();// 드로우
	virtual bool     Release();// 삭제, 소멸
	virtual void     MsgEvent(MSG msg);
public:
	bool Run();
	bool GameRun();
	bool GameInit();
	bool GameFrame();
	bool GameRender();
	bool GameRelease();
public:
	TCore();
	virtual ~TCore();
};

