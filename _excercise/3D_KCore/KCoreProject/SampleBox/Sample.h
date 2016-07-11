#pragma once
#include "kcore.h"
using namespace DX;

struct PNCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	PNCT_VERTEX() {}
	PNCT_VERTEX(D3DXVECTOR3 p0,	D3DXVECTOR3 n0,	D3DXVECTOR4 c0,
	D3DXVECTOR2 t0)
	{
		p = p0, n = n0, c = c0, t = t0;
	}
};
struct VS_CONSTANT_BUFFER
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	float time, vp, z, w;
};
#define MAX_VERTEX 24
class Sample : public KCore
{
public:
	UINT				m_iNumIndex;
	ID3D11Buffer*		m_pVBSide;
	KDXHelper			m_Object;
	VS_CONSTANT_BUFFER	m_cbData;
	PNCT_VERTEX m_VertexCenter[MAX_VERTEX];
	PNCT_VERTEX m_VertexSide[MAX_VERTEX];
	ID3D11ShaderResourceView*   m_pTexSRV[4];
	ID3D11SamplerState*			m_pSamplerState;
	D3DXMATRIX m_matWorld[4];
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	D3DXVECTOR3 m_vEye;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	Sample();
	virtual ~Sample();
};

