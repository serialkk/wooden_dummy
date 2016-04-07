#include "KValue.h"


namespace A_TYPE
{
	KValue::KValue(TCHAR* pData)
	{
		int iLength = _tcslen(pData) + 1;
		int iSize = sizeof(TCHAR) * iLength;
		this->m_szValue = new TCHAR[iSize];
		_tcscpy_s(m_szValue, iSize, pData);
		m_pNext = NULL;
	}


	KValue::~KValue()
	{
		delete m_szValue;
	}
}
namespace B_TYPE
{
	KValue::KValue(TCHAR* pData)
	{
		int iLength = _tcslen(pData) + 1;
		int iSize = sizeof(TCHAR) * iLength;
		this->m_szValue = new TCHAR[iSize];
		_tcscpy_s(m_szValue, iSize, pData);
		m_pNext = NULL;
	}


	KValue::~KValue()
	{
		delete m_szValue;
	}
}