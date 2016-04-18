#pragma once
#include "TShape.h"

class TSprite : public TShape
{
public:
	//TCHAR m_szName[MAX_PATH];
	wstring  m_szName; // string m_szName;
	int   m_iSpriteID;
	int   m_iNumFrame;
	float m_fSecPerRender;	
	int   m_iCurFrame;
	float m_fTimer;
	float m_fLifeTime;
	vector<RECT>   m_rtList;
public:
	void   SetRectArray(vector<RECT> rtList,
		float fLifeTime = 1.0f);
	void   SetSpeed(float fSpeed);
	bool   Frame();
	bool   Render();
	bool   Release();
public:
	TSprite();
	virtual ~TSprite();
};

