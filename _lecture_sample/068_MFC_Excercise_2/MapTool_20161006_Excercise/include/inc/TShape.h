#pragma once
#include "TModel.h"

class TShape : public TModel
{
public:
	D3DXVECTOR3					m_vCenterPos;
	D3DXVECTOR3					m_vMoveDirection;
	float						m_fRadius;
	PCT_VERTEX*					m_pVertexList;
	DWORD*						m_pIndexList;
	//--------------------------------------------------------------------------------------
	// Collision Data
	//--------------------------------------------------------------------------------------
	T_BOX                       m_Box;
    T_SPHERE                    m_Sphere;
    T_PLANE                     m_Plane;
public:	
	virtual void SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	virtual bool ReLoadVertexBuffer(ID3D11DeviceContext*	pImmediateContext);
	//--------------------------------------------------------------------------------------
	// Buffer & Texture Set
	//--------------------------------------------------------------------------------------
	virtual HRESULT			InitBufferData();
	virtual HRESULT			LoadTextures( ID3D11Device* pDevice, const TCHAR* pLoadTextureString);
	//--------------------------------------------------------------------------------------
	// Create Vertex Buffer / Index Buffer
	//--------------------------------------------------------------------------------------
	virtual HRESULT						CreateVertexBuffer();
	virtual HRESULT						CreateIndexBuffer();
	//m_pVertexList를 삭제한 이후에 새로운 정점을 채워서 호출한다.
	virtual bool						ReLoadVertexBuffer();
	//스크린 좌표를 사용하여 정점 위치를 생성한다.
	bool								m_bScreenVertex;
	virtual bool						SetScreenVertex(	float x, 
															float y, 
															float w, 
															float h,
															D3DXVECTOR2 vScreen);

public:
	bool Load( ID3D11Device* pDevice, ID3D11DeviceContext* pd3dImmediateContext, const TCHAR* szTexName, TModel* pFileModel = 0);
	virtual bool			Render(ID3D11DeviceContext*	pImmediateContext);
	// 라인 출력 전용.
	virtual bool						Draw( D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 dwColor = D3DXVECTOR4( 1.0f, 1.0f, 1.0f,1.0f) );
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	virtual HRESULT						CreateResource();
	virtual HRESULT						DeleteResource();	
	virtual bool						Release();
    //--------------------------------------------------------------------------------------
    // Utility
    //--------------------------------------------------------------------------------------
    void	CreateOBBBox(	float fExtX = 1.0f,float fExtY = 1.0f,float fExtZ = 1.0f,
		                    D3DXVECTOR3 vCenter  = D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), 
		                    D3DXVECTOR3 vDirX = D3DXVECTOR3( 1.0f, 0.0f, 0.0f ),
		                    D3DXVECTOR3 vDirY = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ),
		                    D3DXVECTOR3 vDirZ = D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) );
	void	CreateAABBBox(	D3DXVECTOR3 vMax  = D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), 
		                    D3DXVECTOR3 vMin  = D3DXVECTOR3( -1.0f, -1.0f, -1.0f ) );	
    void    CreateSphere();
    void    CreatePlane();
public:
	TShape(void);
	virtual ~TShape(void);
};

class TLineShape: public TShape
{
public:
	HRESULT						InitBufferData();
	HRESULT						CreateResource();
	bool						Draw( ID3D11DeviceContext*	pImmediateContext, D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 dwColor );
public:
	TLineShape(void);
	virtual ~TLineShape(void);
};

class TDirectionLineShape: public TShape
{
public:
	HRESULT						InitBufferData();
	HRESULT						CreateResource();
public:
	TDirectionLineShape(void);
	virtual ~TDirectionLineShape(void);
};

class TBoxShape: public TShape
{
public:
	HRESULT						InitBufferData();
	HRESULT						CreateResource();
	bool						ReLoadVertexBuffer(ID3D11DeviceContext*	pImmediateContext);
public:
	TBoxShape(void);
	virtual ~TBoxShape(void);
};

class TPlaneShape: public TShape
{
public:
	HRESULT						InitBufferData();
	HRESULT						CreateResource();
	bool	SetScreenVertex(	float x, 
								float y, 
								float w, 
								float h,
								D3DXVECTOR2 vScreen );
public:
	TPlaneShape(void);
	virtual ~TPlaneShape(void);
};
class TSphereShape: public TShape
{
public:
	vector<PNCT_VERTEX>			m_VertexList;
	HRESULT						InitBufferData();
	HRESULT						CreateResource();
	bool Render(ID3D11DeviceContext*	pContext);
	bool						Update(ID3D11DeviceContext*	pImmediateContext);
	void CreateSphere( UINT Slices=20, float fRadius=1.0f );
	void MakeSpherePoint(	std::vector<D3DXVECTOR3> &spherePoints,
						 UINT Slices =20, double r= 1.0f, 
						 D3DXVECTOR3 center = D3DXVECTOR3(0,0,0));
public:
	TSphereShape(void);
	virtual ~TSphereShape(void);
};