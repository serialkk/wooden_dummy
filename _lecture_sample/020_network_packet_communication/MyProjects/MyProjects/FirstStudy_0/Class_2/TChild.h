#pragma once
#include "TParent.h"
class TChild : public TParent
{
public:
	int   GetMoney()
	{
		return m_iMoney;
	}
	// 재정의 했다.
	void  SetMoney(int iValue)
	{
		m_iMoney += iValue;
	}
public:
	TChild();
	~TChild();
};

