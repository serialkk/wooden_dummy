#include "KToken.h"
#define SPA _T(" ")


void KToken::Show()
{
	KValue* pData = m_pToken;
	for (int i = 0; i < m_iSize; i++)
	{
		std::wcout << pData->m_szValue << endl;
		pData = pData->m_pNext;
	}
}


KToken::KToken(TCHAR* pData)
{
	int		m_iSize;
	TCHAR*	temp;
	TCHAR*  pszNextToken;
	temp = _tcstok_s(pData, SPA, &pszNextToken);
	if (temp != NULL)
	{
		m_pToken = new KValue(temp);
		KValue* pLink = m_pToken;
		for (m_iSize = 0; temp = _tcstok_s(0, SPA, &pszNextToken); m_iSize++)
		{
			pLink->m_pNext = new KValue(temp);
			pLink = pLink->m_pNext;
		}
	}

}


KToken::~KToken()
{
	KValue* pDel;
	KValue* pLink = m_pToken;
	while(pLink != 0)
	{
		pDel = pLink;
		pLink = pLink->m_pNext;
		delete pDel;
	}
}
