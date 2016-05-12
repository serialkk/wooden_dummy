#pragma once
#include "TStd.h"
enum KeyState {
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD,
};
class TInput
{
public:
	DWORD m_dwKeyState[256];
	DWORD m_dwMouseState[3];
	POINT m_MovePt;
	TCHAR m_csBuffer[MAX_PATH];
	DWORD m_dwBeforeMouseState[3];
public:
	bool     Init(); // 초기화
	bool     Frame();// 계산
	bool     Render();// 드로우
	bool     Release();// 삭제, 소멸
	DWORD    KeyCheck(DWORD dwKey);
	void     MsgEvent(MSG msg);
public:
	TInput();
	~TInput();
};

