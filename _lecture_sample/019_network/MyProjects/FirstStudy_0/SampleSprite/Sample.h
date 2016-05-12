#pragma once
#include "TCore.h"
#include "TBitmap.h"
#include "THero.h"
#include "TEffect.h"

class Sample : public TCore
{
public:
	TBitmap    m_Bitmap;
	typedef vector<RECT>  SPRITE_ARRAY;
	//RECT **m_SpriteList;
	vector<SPRITE_ARRAY>  m_SpriteList;
	THero      m_Hero;
	list<TEffect*>    m_EffectList;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool    LoadSprite(TCHAR* pFileName);
	void	SetSprite(int iIndex, float fLifeTime=1.0f);
public:
	Sample();
	~Sample();
};

