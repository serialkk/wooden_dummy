// vector_0.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

template<class T>
void PRINT( T& data )
{
	T::iterator pos;
	for (	pos = data.begin();
			pos != data.end();
			++pos)
	{		
		std::cout << ((TNode)*pos).data;
	}
}

class TNode
{
public:
	int data;
	int value;
	void Init()
	{
		std::cout << data << endl;
	}
	void Draw( std::string buffer)
	{
		std::cout << buffer << endl;
	}
};
int iFind;
bool Cmp(TNode& iValue)
{
	if (iValue.data == iFind)
	{
		return true;
	}
	return false;
}

int main()
{
	// 배열
	std::list<TNode> vec;
	std::list<TNode*> pec;

	for (int iData = 0; iData < 10; iData++)
	{
		TNode a;
		a.data = iData;
		vec.push_back(a);
	}

	for_each(vec.begin(), vec.end(), 
		       mem_fun_ref(&TNode::Init));
	for_each(vec.begin(), vec.end(),
		bind2nd( mem_fun_ref(&TNode::Draw), "kgca")
		);

	PRINT(vec);


	std::list<TNode>::iterator itor = vec.begin();
	//for (int iCnt = 0; iCnt < vec.size(); iCnt++)
	while( itor != vec.end())
	{				
		std::cout << (*itor).data;
		++itor;
	}
	std::cout << std::endl;

	for (int iData = 0; iData < 10; iData++)
	{
		TNode* a = new TNode;
		//a->data = 10;
		pec.push_back(a);
	}
	for_each(pec.begin(), pec.end(),
		mem_fun(&TNode::Init));

	/*for (int iCnt = 0; iCnt < pec.size(); iCnt++)
	{
		TNode* pNode = pec.
		std::cout << pec[iCnt]->data;
	}*/

	std::cout << std::endl;
	return 0;
}

