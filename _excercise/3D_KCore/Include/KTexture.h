#pragma once
#include "KStd.h"
class KTexture
{
public:
	T_STR		 m_strName;	
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

	bool Load( T_STR fileName );
public:
	KTexture(void);
	~KTexture(void);
};

