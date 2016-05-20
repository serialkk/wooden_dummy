// list.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <set>
#include <map>
using namespace std;

struct TNode
{
	std::map<int, TNode* > map;
	int m_i;
	TNode( int i) : m_i(i)
	{}
	TNode() {}
};
TNode f;
vector<TNode> maplist;
bool cmp(TNode* data)
{		
	TNode a;
	maplist.push_back(a);
	if (f.m_i == data->m_i)
	{
		return true;
	}
	return false;
}
int main()
{
	TNode aaaaa;
	memset(&aaaaa, 0, sizeof(TNode));

	std::map<int, TNode* > map;
	map[0] = new TNode;
	map[1] = new TNode;
	map[2] = new TNode;

	map.insert(make_pair(3, new TNode));
	//std::cout << map[3].;

	std::map<int, TNode* >::iterator iter;
	iter = map.find(3);
	
	

	typedef std::map<int, TNode*>::iterator ITOR;
	for (ITOR itor = map.begin(); itor != map.end();
	itor++)
	{
		TNode* pNode = (TNode*)iter->second;
		delete pNode;
	}

	map.clear();
	///*std::map<int, TNode > map;
	//TNode aa, bb, cc;
	//map[0] = aa;
	//map[1] = bb;
	//map[2] = cc;

	//std::cout << map[0].m_i;*/

	//list<char> list1;
	//list1.push_back('k');
	//list1.push_back('g');
	//list1.push_back('c');
	//list1.clear();

	//multiset<TNode*> list2;
	//set<TNode*> list3;
	//TNode* a = new TNode;
	//TNode* b = new TNode;
	//TNode c, d;
	//list2.insert(a);
	//list2.insert(b);
	//list2.insert(a);
	//int iNum2 = list2.size();
	//int iCnt = count(list2.begin(), list2.end(), b);
	////count_if(list2.begin(), list2.end(), cmp);
	///*list3.insert(c);
	//list3.insert(a);*/

	//list2.insert('k');
	//list2.insert('k');
	//list2.insert('k');
	//list2.insert('a');
	//list2.insert('b');
	//list2.insert('c');
	//list2.insert('d');
	//list2.insert('e');
    return 0;
}

