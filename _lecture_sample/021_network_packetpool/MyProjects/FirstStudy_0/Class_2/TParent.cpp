#include "TParent.h"



TParent::TParent()
{
	this->m_iMoney = 0;
	std::cout << "TParent()" << std::endl;
}
TParent::TParent(int iMoney) : m_iMoney(iMoney)
{
	//this->m_iMoney = iMoney;
	std::cout << "TParent()" << std::endl;
}

TParent::~TParent()
{
	std::cout << "~TParent()" << std::endl;
}
