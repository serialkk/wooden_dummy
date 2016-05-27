#include "TSynchronize.h"



TSynchronize::TSynchronize(TServerObj* pObj) :
	m_pObj( pObj)
{
	if (pObj != NULL)
	{
		EnterCriticalSection(&pObj->m_cs);
	}
}


TSynchronize::~TSynchronize()
{
	if (m_pObj != NULL)
	{
		LeaveCriticalSection(&m_pObj->m_cs);
	}
}
