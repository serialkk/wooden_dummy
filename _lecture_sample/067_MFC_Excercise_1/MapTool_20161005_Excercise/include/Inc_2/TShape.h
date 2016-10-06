#pragma once
#include "TDxState.h"
#include "TDxBuffer.h"
#include "TInputLayout.h"
#include "TViewPort.h"
#include "TTexture.h"
#include "TShader.h"

struct T_PLANE
{
	float	fA,fB,fC,fD;
	bool	CreatePlane( D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2 );
	bool	CreatePlane( D3DXVECTOR3 vNormal, D3DXVECTOR3 v0 );	
	void	Normalize()
	{
		float fMag =  sqrt( fA*fA + fB*fB + fC*fC);
		fA = fA  / fMag;
		fB = fB / fMag;
		fC = fC / fMag;		
		fD = fD / fMag;		
	}

};
struct T_SPHERE
{
	D3DXVECTOR3		vCenter;
	float			fRadius;
};
struct T_BOX
{	
	// Common
	D3DXVECTOR3		vCenter;
    D3DXVECTOR3		vPos[8];
	// AABB
	D3DXVECTOR3		vMax;
	D3DXVECTOR3		vMin;
	// OBB
	D3DXVECTOR3		vAxis[3];
	float			fExtent[3];
};

class TShape
{
public:	
	ID3D11Device*				m_pd3dDevice;
	ID3D11DeviceContext*		m_pImmediateContext;
	//--------------------------------------------------------------------------------------
	// Effect Variables
	//--------------------------------------------------------------------------------------
	TDxBuffer					m_BufferVB;
	TDxBuffer					m_BufferIB;
	//--------------------------------------------------------------------------------------
	// InputLayout Variables
	//--------------------------------------------------------------------------------------
	TInputLayout				m_InputLayout;
	//--------------------------------------------------------------------------------------
	// Matrix
	//--------------------------------------------------------------------------------------
	D3DXMATRIX					m_matWorld;	
	D3DXMATRIX					m_matView;
	D3DXMATRIX					m_matProj;
	D3DXMATRIX					m_matNormal;
	//--------------------------------------------------------------------------------------
	// Effect Variables
	//--------------------------------------------------------------------------------------
	TShader						m_Shader;	
public:
	D3DXVECTOR3					m_vCenterPos;
	D3DXVECTOR3					m_vMoveDirection;
	float						m_fRadius;
	int							m_iNumVertex;
	PCT_VERTEX*					m_pVertexList;
	DWORD*						m_pIndexList;

public:	
	ID3DX11EffectMatrixVariable* m_pWorldVariable;
	ID3DX11EffectMatrixVariable* m_pViewVariable;
	ID3DX11EffectMatrixVariable* m_pProjVariable;
	ID3DX11EffectMatrixVariable* m_pNormalVariable;
	ID3DX11EffectShaderResourceVariable* m_pTextureVariable;

	ID3DX11EffectTechnique*		m_pTechnique;
	ID3DX11EffectTechnique*		m_pTechniqueColor;
	ID3DX11EffectTechnique*		m_pTechniqueOnlyAmbientColor;
	ID3DX11EffectTechnique*		m_pTechniqueApply;

	ID3DX11EffectVectorVariable* m_pAmbientColor;
	ID3D11Buffer*				GetVB();
	ID3D11Buffer*				GetIB();
	void						SetMatrix( D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj );
	void						SetAmbientColor( float fR, float fG, float fB, float fA );
	ID3DX11Effect*				GetEffect() { return m_Shader.GetEffect(); }	
	
	//--------------------------------------------------------------------------------------
	// DrawLine Line State
	//--------------------------------------------------------------------------------------
	TDxState					m_DxState;
	TTexture					m_Texture;
    //--------------------------------------------------------------------------------------
	// Collision Data
	//--------------------------------------------------------------------------------------
	T_BOX                       m_Box;
    T_SPHERE                    m_Sphere;
    T_PLANE                     m_Plane;
public:
	//--------------------------------------------------------------------------------------
	// Effect Variables
	//--------------------------------------------------------------------------------------
	virtual HRESULT						LoadShaderFile(TCHAR* pLoadShaderString=NULL);
	virtual void						GetEffectVariable();
	virtual HRESULT						SetInputLayout();
	virtual void						SetTechnique(ID3DX11EffectTechnique* pTechnique);
	virtual HRESULT						InitBufferData();
	virtual HRESULT						LoadTextures( ID3D11Device* pDevice, TCHAR* pLoadTextureString);
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
	virtual bool						Create( ID3D11Device* pDevice, 
												ID3D11DeviceContext*    pImmediateContext, 
												TCHAR* pLoadTextureString = 0,
												TCHAR* pLoadShaderString = 0 );
	virtual bool						Init();
	virtual bool						Frame();
	virtual bool						Render();
	virtual bool						Render(ID3D11DeviceContext* pContext);
	virtual bool						Release();	
	// 라인 출력 전용.
	virtual bool						Draw( D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 dwColor = D3DXVECTOR4( 1.0f, 1.0f, 1.0f,1.0f) );
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	virtual HRESULT						CreateResource();
	virtual HRESULT						DeleteResource();	
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
	//--------------------------------------------------------------------------------------
	// Effect Variables
	//--------------------------------------------------------------------------------------
	HRESULT						SetInputLayout();
	//--------------------------------------------------------------------------------------
	// Create Vertex Buffer / Index Buffer
	//--------------------------------------------------------------------------------------
	HRESULT						CreateVertexBuffer();
	HRESULT						CreateIndexBuffer();
public:
	bool						Render();
	HRESULT						CreateResource();
public:
	bool						Draw( D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 dwColor );
public:
	TLineShape(void);
	virtual ~TLineShape(void);
};

class TDirectionLineShape: public TShape
{
public:
	//--------------------------------------------------------------------------------------
	// Effect Variables
	//--------------------------------------------------------------------------------------
	HRESULT						SetInputLayout();
	//--------------------------------------------------------------------------------------
	// Create Vertex Buffer / Index Buffer
	//--------------------------------------------------------------------------------------
	HRESULT						CreateVertexBuffer();
	HRESULT						CreateIndexBuffer();
public:
	bool						Render();
	HRESULT						CreateResource();
public:
	TDirectionLineShape(void);
	virtual ~TDirectionLineShape(void);
};

class TBoxShape: public TShape
{
public:
	HRESULT						InitBufferData();
	HRESULT						SetInputLayout();
	HRESULT						CreateVertexBuffer();
	HRESULT						CreateIndexBuffer();
public:
	bool						Render();
	HRESULT						CreateResource();
	bool						ReLoadVertexBuffer();
public:
	TBoxShape(void);
	virtual ~TBoxShape(void);
};

class TPlaneShape: public TShape
{
public:
	HRESULT						InitBufferData();
	HRESULT						SetInputLayout();
	HRESULT						CreateVertexBuffer();
	HRESULT						CreateIndexBuffer();
public:
	bool						Render();
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
	HRESULT						SetInputLayout();
	HRESULT						CreateVertexBuffer();
	HRESULT						CreateIndexBuffer();
public:
	bool						Render();
	HRESULT						CreateResource();
	void CreateSphere( UINT Slices=20, float fRadius=1.0f );
	void MakeSpherePoint(	std::vector<D3DXVECTOR3> &spherePoints,
						 UINT Slices =20, double r= 1.0f, 
						 D3DXVECTOR3 center = D3DXVECTOR3(0,0,0));
public:
	TSphereShape(void);
	virtual ~TSphereShape(void);
};