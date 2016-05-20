#pragma once
#include <windows.h>
#define PACKET_HEADER_SIZE 4
#pragma pack( push, 1)
	typedef struct {
		WORD   len;
		WORD   type;
	}PACKET_HEADER;
	typedef struct {
		PACKET_HEADER ph;
		char   msg[2048];
	}UPACKET, *P_UPACKET;
	typedef struct
	{
		char szName[13];		
		int  iIndex;		
		int  iData[10];
	}CHARACTER_INFO;
#pragma pack(pop)

#define  PACKET_CHAR_MSG   1000
#define  PACKET_CHAR_JOIN   1001
#define  PACKET_CHAR_DROP   1002
#define  PACKET_CREATE_CHARACTER   2000
// YPACKET p;
// p.msg = "kgca"
// p.len = PACKET_HEADER_SIZE  + strlen(p.msg);
// p.type = PACKET_CHAR_MSG;
// send( p... );