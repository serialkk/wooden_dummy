#include "TUser.h"
void        TUser::Dispatch(DWORD dwSize,
	LPOVERLAPPED ov)
{	
	OVERLAPPEDEX* pOV = (OVERLAPPEDEX*)ov;
	if (pOV->iFlag == OVERLAPPEDEX::MODE_RECV)
	{
		m_io.Put( m_szBuffer, dwSize, this );
	}
	else
	{
	}
	
}
TUser::TUser()
{

}
TUser::~TUser()
{

}