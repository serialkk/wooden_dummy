#pragma once
#include "TDxState.h"
#include "TDxBuffer.h"
#include "TInputLayout.h"
#include "TViewPort.h"
#include "TTexture.h"
#include "TShader.h"

class TShape
{
protected:	
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
	//--------------------------------------------------------------------------------------
	// Effect Variables
	//--------------------------------------------------------------------------------------
	TShader						m_Shader;	
public:
	D3DXVECTOR3					m_vCenterPos;
	D3DXVECTOR3					m_vMoveDirection;
	float						m_fRadius;


public:	
	ID3DX11EffectMatrixVariable* m_pWorldVariable;
	ID3DX11EffectMatrixVariable* m_pViewVariable;
	ID3DX11EffectMatrixVariable* m_pProjVariable;
	ID3DX11EffectShaderResourceVariable* m_pTextureVariable;
	ID3DX11EffectTechnique*		m_pTechnique;
	ID3DX11EffectTechnique*		m_pTechniqueColor;
	ID3DX11EffectTechnique*		m_pTechniqueOnlyAmbientColor;
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

public:
	//--------------------------------------------------------------------------------------
	// Effect Variables
	//--------------------------------------------------------------------------------------
	virtual HRESULT						LoadShaderFile();
	virtual void						GetEffectVariable();
	virtual HRESULT						SetInputLayout();
	//--------------------------------------------------------------------------------------
	// Create Vertex Buffer / Index Buffer
	//--------------------------------------------------------------------------------------
	virtual HRESULT						CreateVertexBuffer();
	virtual HRESULT						CreateIndexBuffer();

public:
	virtual bool						Create( ID3D11Device* pDevice, ID3D11DeviceContext*    pImmediateContext, TCHAR* pLoadTextureString = 0);
	virtual bool						Init();
	virtual bool						Frame();
	virtual bool						Render();
	virtual bool						Release();	
	// 라인 출력 전용.
	virtual bool						Draw( D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 dwColor = D3DXVECTOR4( 1.0f, 1.0f, 1.0f,1.0f) );
	
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	virtual HRESULT						CreateResource();
	virtual HRESULT						DeleteResource();	
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
	HRESULT						SetInputLayout();
	HRESULT						CreateVertexBuffer();
	HRESULT						CreateIndexBuffer();
public:
	bool						Render();
	HRESULT						CreateResource();
public:
	TBoxShape(void);
	virtual ~TBoxShape(void);
};

class TPlaneShape: public TShape
{
public:
	HRESULT						SetInputLayout();
	HRESULT						CreateVertexBuffer();
	HRESULT						CreateIndexBuffer();
public:
	bool						Render();
	HRESULT						CreateResource();
public:
	TPlaneShape(void);
	virtual ~TPlaneShape(void);
};