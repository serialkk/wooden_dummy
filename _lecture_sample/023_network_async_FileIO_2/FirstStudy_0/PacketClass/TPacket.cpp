#include "stdafx.h"
#include "TPacket.h"
// m_szBuffer[0][1][2][3]
// TPacket data;
// data << 10;
// data << "ȣ�浿";
int TPacket::PutData( char* pData, int iSize)
{
	memcpy(m_pWritePos, pData, iSize);
	m_pWritePos += iSize;
	m_iDataSize += iSize;
	return iSize;
}
int TPacket::GetData(char* pData, int iSize)
{
	memcpy(pData, m_pReadPos, iSize);
	m_pReadPos += iSize;
	m_iDataSize -= iSize;
	return iSize;
}
TPacket& TPacket::operator << (int iValue)
{
	PutData(reinterpret_cast<char*>(&iValue), sizeof( int ));
	return *this;
}
TPacket& TPacket::operator << (float fValue)
{
	PutData(reinterpret_cast<char*>(&fValue), sizeof(float));
	return *this;
};
TPacket& TPacket::operator << (char* pValue)
{
	int iLen =strlen(pValue);
	PutData(pValue, strlen(pValue)+1);
	return *this;
}
// output
TPacket& TPacket::operator >> (int& iValue)
{
	GetData(reinterpret_cast<char*>(&iValue), sizeof(int));
	return *this;
}
TPacket& TPacket::operator >> (float& fValue)
{
	GetData(reinterpret_cast<char*>(&fValue), sizeof(float));
	return *this;
}
TPacket& TPacket::operator >> (char* pValue)
{
	GetData(pValue, sizeof(char)*6);
	return *this;
}
TPacket::TPacket()
{
	m_pReadPos = m_szBuffer;
	m_pWritePos = m_szBuffer;
	m_iDataSize = 0;
}


TPacket::~TPacket()
{
}
