#pragma once
#include "TWindow.h"
#include "TTimer.h"
#include "TInput.h"

class TCore : public TWindow
{
public :
	TTimer     m_Timer;
	TInput     m_Input;
public:
	virtual bool     Init(); // �ʱ�ȭ
	virtual bool     Frame();// ���
	virtual bool     Render();// ��ο�
	virtual bool     Release();// ����, �Ҹ�
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

