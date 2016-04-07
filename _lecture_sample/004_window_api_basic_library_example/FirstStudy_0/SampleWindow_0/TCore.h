#pragma once
#include "TWindow.h"
#include "TTimer.h"

class TCore : public TWindow
{
public :
	TTimer		m_Timer;
public:
	virtual bool     Init(); // �ʱ�ȭ
	virtual bool     Frame();// ���
	virtual bool     Render();// ��ο�
	virtual bool     Release();// ����, �Ҹ�
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

