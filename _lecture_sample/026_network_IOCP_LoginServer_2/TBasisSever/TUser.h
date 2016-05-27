#pragma once
#include "TServerObj.h"
#include "TStream.h"
typedef struct _OVERLAPPEDEX : OVERLAPPED
{
	enum { MODE_RECV=0, MODE_SEND=1,};
	int iFlag;
	_OVERLAPPEDEX() {
		iFlag = MODE_RECV;
	}
}OVERLAPPEDEX;

class TUser : public TServerObj
{
public:	
	TStream   m_io;
	SOCKET    m_sock;
	SOCKADDR_IN   m_Address;
	OVERLAPPEDEX  m_ov;
	WSABUF		  m_szWsaBuf;
	char		  m_szBuffer[4096];
public:
	virtual void		AddPacket(T_PACKET& tPacket) {};
	virtual void		Delete() {};
	virtual void        Dispatch(DWORD dwSize,
		LPOVERLAPPED ov);

public:
	TUser();
	virtual ~TUser();
};