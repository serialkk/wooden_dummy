#pragma once
#include "TFrustum.h"

class TBaseObj
{
public:
	int					m_iIndex;
	T_BOX				m_tBox;
public:
	 TBaseObj(void);
	 virtual ~TBaseObj(void);
};
