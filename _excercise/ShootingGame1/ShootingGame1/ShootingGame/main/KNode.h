#pragma once
#include <iostream>
#include <tchar.h>
template < class T >
class KNode
{
public:
	T*		m_pData;
	KNode*  m_pNext;
	KNode*  m_pPrev;
public:
	KNode();
	~KNode();
};
template < class T>
KNode<T>::KNode()
{
	m_pData = NULL;
	m_pNext = NULL;
	m_pPrev = NULL;
}
template < class T>
KNode<T>::~KNode()
{
	delete m_pData;
}