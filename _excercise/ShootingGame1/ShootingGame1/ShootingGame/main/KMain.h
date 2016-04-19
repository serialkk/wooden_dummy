#pragma once
#include "KCore.h"
#include "KEnemy.h"
#include "KHero.h"
#include "KSound.h"
#define MAX_OBJECT 100
class KMain : public KCore
{
public:
	KSound		m_pSound;
	KEnemy		m_BackGround;
	KHero		m_Hero;
	KEnemy		m_Object[MAX_OBJECT];
	float			m_iX;
	float			m_iY;
public:
	bool	 Init();
	bool	 Frame();
	bool	 Render();
	bool	 Release();
public:
	KMain();
	virtual ~KMain();
};

