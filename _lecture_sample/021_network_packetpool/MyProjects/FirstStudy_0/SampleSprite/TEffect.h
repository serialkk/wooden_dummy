#pragma once
#include "TSprite.h"
class TEffect //: public TObject
{
public:
	TSprite*  m_pSprite;// 0, 1,2
	bool  Frame()
	{
		m_pSprite->Frame();
	}
	bool  Render()
	{
		m_pSprite->Render();
	}
public:
	TEffect();
	virtual ~TEffect();
};

