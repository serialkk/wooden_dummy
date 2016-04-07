#pragma once
#include "KWindow.h"
class KCore : public KWindow
{
public:
	virtual bool Init(); //초기화
	virtual bool Frame();//계산
	virtual bool Render();//드로우
	virtual bool Release();//삭제, 소멸
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

