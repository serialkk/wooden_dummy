#pragma once
#include <iostream>
#include <tchar.h>
using namespace std;
namespace A_TYPE
{
	class KValue
	{
	private:
		TCHAR*		m_szValue;
		KValue*		m_pNext;
		friend class KToken;
	public:
		KValue(TCHAR* pValue);
		~KValue();
	};
}
namespace B_TYPE
{
	class KValue
	{
	public:
		TCHAR*		m_szValue;
		KValue*		m_pNext;
		friend class KToken;
	public:
		KValue(TCHAR* pValue);
		~KValue();
	};
}
