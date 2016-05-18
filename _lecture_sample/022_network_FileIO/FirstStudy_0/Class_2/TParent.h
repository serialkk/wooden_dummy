#pragma once
#include<iostream>
class TParent
{
protected:	
	int		m_iMoney;
public:
	// ���� ���� �Լ�
	virtual int		GetMoney() = 0;
	// �����Լ�
	virtual void		SetMoney(int iMoney) {
		m_iMoney = iMoney;
	}
public:
	TParent();
	TParent(int iMoney);
	virtual ~TParent();
};

class Ta : public TParent
{
public:
	void		SetMoney(int iMoney) {
		m_iMoney = iMoney*2;
	}
	int 		GetMoney() {
		return m_iMoney;
	}
	~Ta()
	{
		std::cout << "~Ta" << std::endl;
	}
};
class Tb : public TParent
{
public:
//	void		SetMoney(int iMoney) {
//		m_iMoney = iMoney/2;
//	}
	int 		GetMoney() {
		return m_iMoney;
	}
	~Tb()
	{
		std::cout << "~Tb" << std::endl;
	}
};
class Tc : public TParent
{
public:
	void		SetMoney(int iMoney) {
		m_iMoney = iMoney-100;
	}
	int 		GetMoney() {
		return m_iMoney;
	}
	~Tc()
	{
		std::cout << "~Tc" << std::endl;
	}
};

class TManager
{
public:
	TParent*  m_pData[3];
	void  Add(TParent* pData, int iIndex)
	{
		m_pData[iIndex] = pData;
	}
	void  Show()
	{
		for (int i = 0; i < 3; i++)
		{
			std::cout << m_pData[i]->GetMoney();
		}
	}
};