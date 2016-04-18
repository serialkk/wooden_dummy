#pragma once
#include "TCore.h"
#include "TBitmap.h"
class Sample : public TCore
{
public:
	TBitmap    m_BackGround;
	TBitmap    m_ColorBitmap;
	TBitmap    m_MaskBitmap;
	float      m_fAngle;
	HBRUSH	   m_back;
	RECT	   m_rt;
	HDC		   m_RotationBitmapDC;
	HDC        m_hMaskMemDC;
	HDC        m_hColorMemDC;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	void		DrawObject();
	void		DrawBackGround();
	void		DrawRotate(float fAngle);
	HBITMAP		GetRotationBimap(HDC hdc,
				float fAngle, 
				int iWidth, 
				int iHeight);
public:
	Sample();
	virtual ~Sample();
};

