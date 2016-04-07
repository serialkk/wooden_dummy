#pragma once
#include "TCore.h"
#include "TTimer.h"

class Sample : public TCore
{
public:
	TTimer   m_Timer;
public:
	bool	 Init();
	bool	 Frame();
	bool	 Render();
	bool	 Release();
public:
	Sample();
	virtual ~Sample();
};

