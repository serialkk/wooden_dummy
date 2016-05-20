#include "TChild.h"



TChild::TChild() : TParent(10000000)
{
	std::cout << "TChild()" << std::endl;
}


TChild::~TChild()
{
	std::cout << "~TChild()" << std::endl;
}
