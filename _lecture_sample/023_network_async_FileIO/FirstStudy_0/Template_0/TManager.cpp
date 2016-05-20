#include "TManager.h"
template< typename T >
void SwapPoint( T* a, T* b)
{
	a->m_pNext = b;
	b->m_pPrev = a;
}
TNode<TStudent> * TManager::Swap(
	TNode<TStudent>* a, TNode<TStudent>* b )
{
	TNode<TStudent> * aPrev = a->m_pPrev;
	TNode<TStudent> * aNext = a->m_pNext;
	TNode<TStudent> * bPrev = b->m_pPrev;
	TNode<TStudent> * bNext = b->m_pNext;

	// 1번 Haed <-> b
	if (aPrev != NULL)	{ 	SwapPoint(aPrev, b);	
	}else{	m_List.m_pHead = b;	
			b->m_pPrev = NULL;	}
	// b <-> a
	if(aNext != b)
	{
		SwapPoint(b, aNext);	
		// a -> c -> b
		if( aNext->m_pNext == b )	SwapPoint(aNext, a);
		else						SwapPoint(bPrev, a);
	}
	else // b <-> a
	{
		SwapPoint(b, a);
		a->m_pNext = bNext;
		if (bNext != NULL) bNext->m_pPrev = a;
	}
	// a-> c -> b ->d
	if (bNext != NULL)  SwapPoint(a, bNext);
	else				a->m_pNext = NULL;

	if (aNext == b) return a;
	return aNext;
}
// iCnt 명에 대한 학생을 랜덤하게 구성.
bool   TManager::InputData(int iCnt)
{
	for (int istd = 0; istd < iCnt; istd++)
	{
		TStudent* pStudent = new TStudent;
		for (int iName = 0; iName < 5; iName++)
		{
			char cWord = 65 + rand() % 26;
			pStudent->m_szName[iName] = cWord;
		}
		pStudent->m_szName[4] = 0;
		pStudent->m_iIndex = istd;
		pStudent->m_Subject.m_iKor = rand() % 101;
		pStudent->m_Subject.m_iEng = rand() % 101;
		pStudent->m_Subject.m_iMat = rand() % 101;
		pStudent->m_iTotal = pStudent->m_Subject.m_iKor +
			pStudent->m_Subject.m_iEng+
			pStudent->m_Subject.m_iMat;
		m_Hash.Insert(pStudent);
		m_List.AddLink(pStudent);		
	}	
	return true;
}

TStudent*  TManager::Find(int iIndex)
{
	for (TNode<TStudent>* pLink = m_List.m_pHead;
	pLink != NULL;
		pLink = pLink->m_pNext)
	{
		TStudent* pData = pLink->m_pData;
		if (pData->m_iIndex == iIndex)
		{
			return pData;
		}
	}
	return NULL;
}
TStudent*  TManager::Find(TCHAR* pszName)
{
	int iIndex = this->m_Hash.Hash(pszName);
	if (iIndex >= m_Hash.m_iLength) return NULL;
	return m_Hash.m_pArray[iIndex].GetData(pszName);		
}
void    TManager::Sort(bool bUp )
{
	TNode<TStudent>* pNodeSrc = m_List.GetHead();
	while(pNodeSrc && pNodeSrc->m_pNext)
	{
		TNode<TStudent>* pNodeSwap = pNodeSrc;
		TStudent* pSrcStudent = pNodeSwap->m_pData;
		for (TNode<TStudent>* pNodeDesk = pNodeSrc->m_pNext;
				pNodeDesk != NULL;
			pNodeDesk = pNodeDesk->m_pNext)
		{
			TStudent* pDeskStudent = pNodeDesk->m_pData;
			if (pNodeSwap->m_pData->m_iTotal > pDeskStudent->m_iTotal)
			{
				pNodeSwap = pNodeDesk;
			}
		}
		if (pNodeSrc != pNodeSwap)
		{
			pNodeSrc = Swap(pNodeSrc, pNodeSwap);
		}
		else
		{
			pNodeSrc = pNodeSrc->m_pNext;
		}		
	}
}
void    TManager::Release()
{
	m_List.Release();	
}
void    TManager::ShowData()
{
	for (TNode<TStudent>* pLink = m_List.m_pHead;
		pLink != NULL;
			pLink = pLink->m_pNext)
	{ 
		TStudent* pData = pLink->m_pData;
		wcout << pData->m_iIndex << " "
			<< pData->m_szName << " "
			<< pData->m_Subject.m_iKor << " "
			<< pData->m_Subject.m_iEng << " "
			<< pData->m_Subject.m_iMat << " "
			<< pData->m_iTotal << " "
			<< endl;			 
	}
}
void    TManager::ShowData(TStudent* pStd)
{
	if (pStd == NULL) return;
	wcout << " ========= " << pStd->m_iIndex << " "
		<< pStd->m_szName << " "
		<< pStd->m_Subject.m_iKor << " "
		<< pStd->m_Subject.m_iEng << " "
		<< pStd->m_Subject.m_iMat << " "
		<< pStd->m_iTotal << " "
		<< endl;
}

TManager::TManager()
{
}


TManager::~TManager()
{
}
