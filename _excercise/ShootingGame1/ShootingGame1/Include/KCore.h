#pragma once
#include "KWindow.h"
#include "KTimer.h"
#include "KInput.h"

class KCore : public KWindow
{
public:
	HDC			m_hScreenDC;  // �� 1 DC => ���
	// �� 2 DC=> ����
	HDC			m_hOffScreenDC;
	// �� 2 DC�� ��Ʈ��
	HBITMAP		m_hOffScreenBitmap;
public :
	KTimer     m_Timer;
	KInput     m_Input;
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
	KCore();
	virtual ~KCore();
};

