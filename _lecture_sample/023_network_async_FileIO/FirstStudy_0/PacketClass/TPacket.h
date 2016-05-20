#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#define MAX_BUFFER_SIZE 2048
typedef std::basic_string<wchar_t>  t_Str;
typedef std::basic_string<char>  c_Str;
using namespace std;

class TPacket
{
public:
	char m_szBuffer[MAX_BUFFER_SIZE];
	char* m_pReadPos;
	char* m_pWritePos;
	int   m_iDataSize;
public:
	int PutData(char* pData, int iSize);
	int GetData(char* pData, int iSize);
public:
	// input
	TPacket& operator << (int iValue);
	TPacket& operator << (float fValue);
	TPacket& operator << (char* pValue);
	//TPacket& operator << (char cValue);
	//TPacket& operator << (TCHAR* pValue);
	//TPacket& operator << (short iValue);
	//TPacket& operator << (WORD fValue);
	//TPacket& operator << (DWORD pValue);
	//TPacket& operator << (c_Str pValue);
	// output
	TPacket& operator >> (int& iValue);
	TPacket& operator >> (float& fValue);
	TPacket& operator >> (char* pValue);
public:
	TPacket();
	virtual ~TPacket();
};

