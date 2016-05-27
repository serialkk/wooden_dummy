#pragma once
#include "TServerObj.h"
class TSynchronize
{
public:
	TServerObj* m_pObj;
public:
	TSynchronize(TServerObj* pObj);
	virtual ~TSynchronize();
};

