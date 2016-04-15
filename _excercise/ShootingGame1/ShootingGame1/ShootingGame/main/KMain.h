#pragma once
#include "KCore.h"
#include "KTimer.h"
#include "KInput.h"

class KMain : public KCore
{
public:
	KTimer   m_Timer;
	KInput   m_Input;
public:
	void     MsgEvent(MSG msg);
	bool	 Init();
	bool	 Frame();
	bool	 Render();
	bool	 Release();
public:
	KMain();
	virtual ~KMain();
};
