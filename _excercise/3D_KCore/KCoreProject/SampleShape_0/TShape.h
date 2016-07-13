#pragma once
#include "KDXHelperEx.h"
using namespace DX;

struct PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;	
	PCT_VERTEX() {}
	PCT_VERTEX( D3DXVECTOR3 p0,
				D3DXVECTOR4 c0,
				D3DXVECTOR2 t0 )
	{
		p = p0;
		c = c0;
		t = t0;
	}
};
struct PNCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	PNCT_VERTEX() {}
	PNCT_VERTEX(D3DXVECTOR3 p0, D3DXVECTOR3 n0,
				D3DXVECTOR4 c0,
				D3DXVECTOR2 t0)
	{
		p = p0;
		n = n0;
		c = c0;
		t = t0;
	}
};
struct PC_VERTEX
{
	D3DXVECTOR3 p;	
	D3DXVECTOR4 c;	
	PC_VERTEX() {}
	PC_VERTEX(D3DXVECTOR3 p0,
		D3DXVECTOR4 c0)
	{
		p = p0;
		c = c0;		
	}
};
struct VS_CONSTANT_BUFFER
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	D3DXVECTOR4 Color;
};

class TShape
{
public:
	ID3D11Device*		m_pd3dDevice;
	KDXObject           m_Object;
	VS_CONSTANT_BUFFER	m_cbData;
	std::vector<DWORD>  m_IndexList;
	D3DXMATRIX			m_matWorld;
	D3DXMATRIX			m_matView;
	D3DXMATRIX			m_matProj;
public:
	void   SetMatrix( D3DXMATRIX* pWolrd, 
		D3DXMATRIX* pView, 
		D3DXMATRIX* pProj );
	virtual bool  Create(ID3D11Device* g_pd3dDevice,
		TCHAR* pShaderFile,
		TCHAR* pTextureFile);
	virtual bool  Render(ID3D11DeviceContext*   pContext);
	virtual HRESULT CreateVertexBuffer() { return true; };
	virtual HRESULT CreateIndexBuffer() { return true; };
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT SetInputlayout() { return true; };
	virtual HRESULT LoadShaderFile(TCHAR* pShaderFile);
	virtual HRESULT LoadShaderResourceView(TCHAR* pTextureFile);
public:
	TShape();
	virtual ~TShape();
};
class TBoxShape : public TShape
{
public:
	std::vector<PNCT_VERTEX>  m_VertexList;
public:
	/*HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	HRESULT SetInputlayout();*/
public:
	TBoxShape() {};
	virtual ~TBoxShape() {};
};
class TPlaneShape : public TShape
{
public:
	std::vector<PCT_VERTEX>  m_VertexList;
public:
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	HRESULT SetInputlayout();
public:
	TPlaneShape() {};
	virtual ~TPlaneShape() {};
};
class TLineShape : public TShape
{
public:
	std::vector<PC_VERTEX>  m_VertexList;
public:
	/*HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	HRESULT SetInputlayout();*/
public:
	TLineShape() {};
	virtual ~TLineShape() {};
};