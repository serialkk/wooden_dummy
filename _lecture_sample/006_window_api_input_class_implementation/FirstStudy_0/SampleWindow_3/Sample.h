#pragma once
#include "TCore.h"
#include "TBitmap.h"
class Sample : public TCore
{
public:
	HDC			m_hScreenDC;
	TBitmap		m_BackGround;
	TBitmap		m_Hero;
	float			m_iX;
	float			m_iY;
public:
	bool	 Init();
	bool	 Frame();
	bool	 Render();
	bool	 Release();
public:
	Sample();
	virtual ~Sample();
};

