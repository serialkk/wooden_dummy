#pragma once
#include "TWindow.h"
#include "TTimer.h"
#include "TInput.h"

class TCore : public TWindow
{
public:
	HDC			m_hScreenDC;  // �� 1 DC => ���
	// �� 2 DC=> ����
	HDC			m_hOffScreenDC;
	// �� 2 DC�� ��Ʈ��
	HBITMAP		m_hOffScreenBitmap;
public :
	TTimer     m_Timer;
	TInput     m_Input;
public:
	virtual bool     Init(); // �ʱ�ȭ
	virtual bool     Frame();// ���
	virtual bool     PreRender();// ��ο�
	virtual bool     Render();// ��ο�
	virtual bool     PostRender();// ��ο�
	virtual bool     Release();// ����, �Ҹ�
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
	TCore();
	virtual ~TCore();
};

