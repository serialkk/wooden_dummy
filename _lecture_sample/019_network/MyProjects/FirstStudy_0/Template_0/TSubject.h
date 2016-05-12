#pragma once
#include <iostream>
#include <tchar.h>
using namespace std;

class TSubject
{
public:
	int		m_iKor;
	int		m_iEng;
	int		m_iMat;
public:
	TSubject();
	virtual ~TSubject();
};

