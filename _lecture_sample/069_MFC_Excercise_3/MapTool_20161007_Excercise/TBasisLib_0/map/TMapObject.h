#pragma once
#include "../TBaseObj.h"
#include "../TBoxObj.h"

#define NUM_OBJECTS 1000

class TMapObject : public TBaseObj
{
public:
	D3DXMATRIX				m_matWorld;	
	D3DXVECTOR3			m_vPosition;
	D3DXVECTOR4			m_vColor;
	TBoxObj*					m_pBoxObj;
public:
	void				Update();	
	void				SetPosition( D3DXVECTOR3 vPos );
public:
	TMapObject();
	~TMapObject();
};