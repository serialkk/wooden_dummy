#pragma once
#include "TCore.h"
#include "TTimer.h"
#include "TInput.h"

class Sample : public TCore
{
public:
	TTimer   m_Timer;
	TInput   m_Input;
public:
	void     MsgEvent(MSG msg);
	bool	 Init();
	bool	 Frame();
	bool	 Render();
	bool	 Release();
public:
	Sample();
	virtual ~Sample();
};

