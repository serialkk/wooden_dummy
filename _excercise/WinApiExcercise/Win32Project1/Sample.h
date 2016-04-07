#pragma once
#include "KCore.h"
//#include "TTimer.h"

class Sample : public KCore
{
public:
	//TTimer   m_Timer;
public:
	bool	 Init();
	bool	 Frame();
	bool	 Render();
	bool	 Release();
public:
	Sample();
	virtual ~Sample();
};

