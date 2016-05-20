#pragma once
#include "TCore.h"
#include "TEnemy.h"
#include "THero.h"
#include "TSound.h"
#define MAX_OBJECT 100
class Sample : public TCore
{
public:
	TSound		m_pSound;
	TEnemy		m_BackGround;
	THero		m_Hero;
	TEnemy		m_Object[MAX_OBJECT];
	float			m_iX;
	float			m_iY;
public:
	bool	 Init();
	bool	 Frame();
	bool	 Render();
	bool	 Release();
	void     DebugString();
public:
	Sample();
	virtual ~Sample();
};

