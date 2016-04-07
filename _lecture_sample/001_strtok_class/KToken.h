#pragma once
#include "KValue.h"
using namespace B_TYPE;
class KToken
{
public:
	KValue*		m_pToken;
	int			m_iSize;
public:
	void		Show();
	KToken(TCHAR* pData);
	~KToken() {};
};

