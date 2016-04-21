#pragma once

#include "THashTable.cpp"
#include "TStudent.h"

class TManager
{
public:
	TLinkedList<TStudent>   m_List;
	THashTable<TStudent>    m_Hash;
private:
	TLinkedList<TStudent>   m_InitList;	
public:	
	bool   InputData(int iCnt);
	TStudent*  Find(int iIndex);
	void    Sort(bool bUp=true);
	void    Release();
	void    ShowData();
	void    ShowData(TStudent* pStd);
	void    Delete(int iIndex) {};
	void    Delete(TStudent* iData) {};
	TNode<TStudent> * Swap(
			TNode<TStudent>* a, 
			TNode<TStudent>* b);
	TStudent*  Find(TCHAR* pszName);
public:
	TManager();
	virtual ~TManager();
};

