#pragma once
#include "KStd.h"
enum KeyState {
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD,
};
class KInput
{
public:
	DWORD m_dwKeyState[256];
	DWORD m_dwMouseState[3];
	POINT m_MovePt;
	TCHAR m_csBuffer[MAX_PATH];
public:
	bool     Init(); // �ʱ�ȭ
	bool     Frame();// ���
	bool     Render();// ��ο�
	bool     Release();// ����, �Ҹ�
	DWORD    KeyCheck(DWORD dwKey);
	void     MsgEvent(MSG msg);
public:
	KInput();
	~KInput();
};

