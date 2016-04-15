#include "TToken.h"
#define SPA _T(" ")
class Exp
{
public:
	void Show(TCHAR* pData)
	{
		std::wcout << pData;
	}
public:
	Exp() {};
	~Exp() {};
};
namespace A_TYPE
{
	TValue::TValue(TCHAR* pData)
	{
		int iLength = _tcslen(pData) + 1;
		int iSize = sizeof(TCHAR) * iLength;
		this->m_szValue = new TCHAR[iSize];
		_tcscpy_s(m_szValue, iSize, pData);
		m_pNext = NULL;
	}
	TValue::~TValue()
	{
		delete m_szValue;
	}
}
namespace B_TYPE
{
	TValue::TValue(TCHAR* pData)
	{
		int iLength = _tcslen(pData) + 1;
		int iSize = sizeof(TCHAR) * iLength;
		this->m_szValue = new TCHAR[iSize];
		_tcscpy_s(m_szValue, iSize, pData);
		m_pNext = NULL;
	}
	TValue::~TValue()
	{
		delete m_szValue;
	}
}

void TToken::Show()
{
	TValue* pData = m_pToken;
	for (int i = 0; i < m_iSize; i++)
	{
		std::wcout << pData->m_szValue << endl;
		pData = pData->m_pNext;
	}
}
TToken::TToken(TCHAR* pData) 
{
	m_iSize = 0;
	TCHAR* temp;
	TCHAR* pszNextToken=0;
	try {

		int iNum = 100;
		int iID = 1;
		if( iID == 0) throw(iID);
		{
			if (pszNextToken == 0) //throw(pszNextToken);
				throw Exp();
			iNum /= iID;

			temp = _tcstok_s(0, SPA, &pszNextToken);
			if (temp != NULL)
			{
				m_pToken = new TValue(temp);
				TValue* pLink = m_pToken;
				for (m_iSize = 1;
				temp = _tcstok_s(0, SPA, &pszNextToken);
					m_iSize++)
				{
					pLink->m_pNext = new TValue(temp);
					pLink = pLink->m_pNext;
				}
			}
		}
	}
	catch (int iNum)
	{
		std::wcout << _T("Error!");
	}
	catch (TCHAR* pszNextToken)
	{
		std::wcout << _T("Error!");
		throw(pszNextToken);
	}
	catch(Exp& exp)
	{ 
		exp.Show(_T("error"));
	}
}
TToken::~TToken() 
{
	TValue* pDel;
	TValue* pLink = m_pToken;
	while (pLink != 0)
	{
		pDel = pLink;
		pLink = pLink->m_pNext;
		delete pDel;
	}
};