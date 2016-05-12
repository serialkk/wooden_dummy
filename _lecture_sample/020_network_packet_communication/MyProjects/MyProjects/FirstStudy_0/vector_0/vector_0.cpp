// vector_0.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

struct TNode
{
	int data;
	int value;
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
//template < typename T > 
//struct TCheck
//{
//	bool operator(T& val) ()
//	{
//		return (val.data == cCompare);
//	}
//};
int main()
{
	std::vector<int> data;
	data.insert(data.begin(), 10);
	data.insert(data.begin(), 20);

	//data.push_back(1);
	//data.push_back(2);
	//data.push_back(3);
	//data.push_back(4);

	//std::vector<int>::iterator itor = 
	//	find(data.begin(), data.end(), 2);
	//data.erase(itor);



	// 배열
	std::vector<TNode> vec;
	std::vector<TNode*> pec;	
	TNode a;
	a.data = 10;
	vec.push_back(a);
	TNode b;
	b.data = 20;
	vec.push_back(b);

	iFind = 20;
	std::vector<TNode>::iterator itor =
		find_if(vec.begin(), vec.end(), Cmp);

	vec.erase(itor);


	//TNode *b = new TNode;
	//b->data = 20;
	//pec.push_back(b);

	//while (pec.size() > 0)
	//{
	//	TNode* pData = pec.front();
	//	std::cout << pData->data;
	//	delete pData;
	//	//pec.erase(pec.begin());
	//}

	////for (int i = 0; i < vec.size(); i++)
	//{
	//	std::cout << vec[i];
	//}
	///*vec.erase(vec.begin());
	//vec.erase(vec.begin());
	//vec.erase(vec.begin());*/

	//std::vector<int>::reverse_iterator tNode;
	//while (vec.size() > 0)
	//{
	//	std::cout << vec.front();
	//	vec.erase(vec.begin());
	//}
	////

	////for (int i = 0; i < 3; i++)
	////{
	////	//std::cout << *tNode;
	////	vec.erase(vec.begin());
	////	size = vec.capacity(); // 메모리 공간 크기
	////}	
	////size = vec.capacity(); // 메모리 공간 크기
	vec.clear();

    return 0;
}

