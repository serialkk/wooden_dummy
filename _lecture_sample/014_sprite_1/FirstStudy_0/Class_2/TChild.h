#pragma once
#include "TParent.h"
class TChild : public TParent
{
public:
	int   GetMoney()
	{
		return m_iMoney;
	}
	// ������ �ߴ�.
	void  SetMoney(int iValue)
	{
		m_iMoney += iValue;
	}
public:
	TChild();
	~TChild();
};

