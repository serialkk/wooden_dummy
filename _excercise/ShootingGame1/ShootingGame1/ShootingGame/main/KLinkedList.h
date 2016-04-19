#pragma once
#include "KNode.h"

template < class T >
class KLinkedList
{
public:
	int		m_iCount;
	KNode<T>*		m_pHead;
	KNode<T>*		m_pTail;
	KNode<T>*		GetHead();
	T*				GetData(int iIndex)
	{
		KNode<T>* pNode = m_pHead;
		while (pNode != NULL)
		{
			if (pNode->m_pData->m_iIndex
				== iIndex)
			{
				return pNode->m_pData;
			}
			pNode = pNode->m_pNext;
		}
		return NULL;
	};
	T*				GetData(TCHAR* pszData)
	{
		KNode<T>* pNode = m_pHead;
		while (pNode != NULL)
		{
			if (_tcsicmp(pNode->m_pData->m_szName,
				pszData) == 0)
			{
				return pNode->m_pData;
			}
			pNode = pNode->m_pNext;
		}
		return NULL;
	};

	bool	AddLink(T* pLink);
	void	Release();
	void    Delete(int iIndex) {};
	void    Delete(T* iData) {};
	void    Delete(KNode<T>* pNode) {};
public:
	KLinkedList();
	~KLinkedList();
};
#pragma region func
template <class T>
void	KLinkedList<T>::Release()
{
	KNode<T>* pDelNode = 0;
	KNode<T>* pNode = m_pHead;
	while (pNode != NULL)
	{
		pDelNode = pNode;
		pNode = pNode->m_pNext;
		delete pDelNode;
	}
	m_pHead = 0;
	m_pTail = 0;
}
template <class T>
KNode<T>*	KLinkedList<T>::GetHead()
{
	return m_pHead;
}
template <class T>
bool	KLinkedList<T>::AddLink(T* pData)
{
	KNode<T>*  pNode = new KNode<T>();
	pNode->m_pData = pData;
	if (m_pHead == NULL)
	{
		m_pHead = pNode;
		m_pTail = pNode;
	}
	else
	{
		KNode<T>* pTemp = m_pHead;
		m_pHead = pNode;
		m_pHead->m_pNext = pTemp;
		pTemp->m_pPrev = pNode;
	}
	m_iCount++;
	return true;
}
template <class T>
KLinkedList<T>::KLinkedList()
{
	m_iCount = 0;
	m_pHead = NULL;
	m_pTail = NULL;
}
template <class T>
KLinkedList<T>::~KLinkedList()
{
}
#pragma endregion