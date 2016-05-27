#pragma once
#include "TThread.h"
class TWorkThread : public TThread
{
public:
	bool		Run();
public:
	TWorkThread();
	virtual ~TWorkThread();
};

