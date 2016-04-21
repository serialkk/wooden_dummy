#pragma once
#include "TStd.h"
#include "TBitmap.h"
class TShape
{
public:
	TBitmap*   m_pColor; 
	TBitmap*   m_pMask;
	RECT     m_rtDraw;
	POINT    m_Position;
public:
	virtual bool	   Load(TCHAR* pColor, 
		TCHAR* pMask);
	virtual bool   Init();
	virtual bool   Frame();
	virtual bool   Render();
	virtual bool   Release();
public:
	TShape();
	virtual ~TShape();
};

