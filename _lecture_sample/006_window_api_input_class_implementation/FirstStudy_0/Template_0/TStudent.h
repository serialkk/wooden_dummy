#pragma once
#include "TSubject.h"
class TStudent 
{
public:
	int			m_iIndex;
	TCHAR		m_szName[5];
	int			m_iTotal;
	float		m_fAverage;
	TSubject	m_Subject;	
public:
	TStudent();
	virtual ~TStudent();
};

