#pragma once
#include "TCore.h"
#include "TBitmap.h"
#include <vector>
using namespace std;

class Sample : public TCore
{
public:
	TBitmap    m_Bitmap;
	typedef vector<RECT>  SPRITE_ARRAY;
	//RECT **m_SpriteList;
	vector<SPRITE_ARRAY>  m_SpriteList;
	float m_fSecPerRender;
	int   m_iSpriteID;
	int   m_iFrame;
	float m_fTimer;
	float m_fLifeTime;

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

