#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#pragma once
class CBox
{
public:
	char m_szStr[256];
	int m_iNum;
	CBox();
	CBox(char* szStr, int iNum) {
		strcpy(m_szStr,szStr);
		m_iNum = iNum;
	}
	virtual ~CBox();
};

