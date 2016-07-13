#pragma once
#include "Kcore.h"
#include "TShape.h"
#define MAX_CNT 100
class Sample : public KCore
{
public:
	TShape* 	 m_pPlane[MAX_CNT];
	D3DXMATRIX   m_matWorld[MAX_CNT];
	D3DXMATRIX   m_matView;
	D3DXMATRIX   m_matProj;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	Sample();
	virtual ~Sample();
};

