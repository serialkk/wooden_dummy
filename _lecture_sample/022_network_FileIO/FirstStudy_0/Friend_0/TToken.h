#pragma once
#include <iostream>
#include <tchar.h>
using namespace std;
class TToken;
namespace A_TYPE
{
	class TValue
	{
	private:
		TCHAR*		m_szValue;
		TValue*		m_pNext;
		friend class TToken;
	public:
		TValue(TCHAR*);
		~TValue();
	};
}
namespace B_TYPE
{
	class TValue
	{
	public:
		TCHAR*		m_szValue;
		TValue*		m_pNext;		
	public:
		TValue(TCHAR*);
		~TValue();
	};
}

#ifdef ATYPE
	using namespace A_TYPE;
#else
	using namespace B_TYPE;
#endif

class TToken
{
public:
	TValue*		m_pToken;
	int			m_iSize;
public:
	void		Show();
	TToken(TCHAR* pData);
	~TToken();
};
