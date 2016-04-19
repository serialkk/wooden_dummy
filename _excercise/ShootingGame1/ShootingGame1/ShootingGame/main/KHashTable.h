#pragma once
#include "KLinkedList.h"
template < class T >
class KHashTable
{
public:
	KLinkedList<T>*		m_pArray;
	int					m_iLength;
	int					Hash(TCHAR* pName);
	void				Insert(T* newItem);
	T*					Find(TCHAR* pszName);
public:
	KHashTable(int iLength = 20);
	~KHashTable();
};
template < class T >
int	KHashTable<T>::Hash(TCHAR* pName)
{
	int iKey = 5381;
	int c;
	size_t hash = 0x811c9dc5;
	while (c = *pName++)
	{
		hash ^= c;
		hash *= 0x01000193;
	}
	/*int c;
	while (c = *pName++)
	{
	iKey = ((iKey << 5) + iKey) + c;
	}*/
	/*int iValue = 0;
	int iLen = _tcslen(pName);
	for (int i = 0; i < iLen; i++)
	{
	iValue += pName[i];
	}
	int iKey = (iValue * iValue) % m_iLength;*/
	return hash % m_iLength;
}
template < class T >
void KHashTable<T>::Insert(T* newItem)
{
	int iIndex = Hash(newItem->m_szName);
	m_pArray[iIndex].AddLink(newItem);
};
template < class T >
T* KHashTable<T>::Find(TCHAR* pszName)
{
	int iIndex = Hash(pszName);
	return m_pArray[iIndex].GetData(pszName);
};

template < class T >
KHashTable<T>::KHashTable(int iLength)
{
	m_pArray = new KLinkedList<T>[iLength];
	m_iLength = iLength;
}
template < class T >
KHashTable<T>::~KHashTable()
{
	delete[] m_pArray;
}