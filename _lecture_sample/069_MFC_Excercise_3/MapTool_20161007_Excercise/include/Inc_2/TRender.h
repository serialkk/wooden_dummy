#pragma once
#include "TInputLayout.h"
#include "TShader.h"
#include "TDxBuffer.h"

class TRender
{
public:
	ID3D11Device*				m_pd3dDevice;
	ID3D11DeviceContext*		m_pImmediateContext;
	UINT						m_iVertexSize;
	UINT						m_iIndexSize;
	//--------------------------------------------------------------------------------------
	// 버텍스 버퍼
	//--------------------------------------------------------------------------------------	
	TDxBuffer					m_BufferVB;
	TDxBuffer					m_BufferIB;
	//--------------------------------------------------------------------------------------
	// Effect Variables
	//--------------------------------------------------------------------------------------
	ID3DX11EffectTechnique*		m_pTechnique;
	ID3DX11EffectTechnique*		m_pTechniqueColor;
	ID3DX11EffectTechnique*		m_pTechniqueApply;	
	//--------------------------------------------------------------------------------------
	// 버텍스 버퍼 및 레이아웃
	//--------------------------------------------------------------------------------------	
	TInputLayout				m_InputLayout;
	TShader*					m_pShader;
	int							m_iShaderID;
	DWORD						m_dwShaderIndex;
	//--------------------------------------------------------------------------------------
	// 행렬
	//--------------------------------------------------------------------------------------		
	D3DXMATRIX					m_matWorld;
	D3DXMATRIX					m_matView;
	D3DXMATRIX					m_matProj;

public:
	virtual void	SetMatrix( D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj );
	virtual void	SetTechnique(ID3DX11EffectTechnique* pTechnique);
	virtual void	GetEffectVariable();	
	virtual HRESULT SetInputLayout();
	virtual bool	LoadShaderFile(int iShaderID);
	virtual HRESULT LoadShaderFile(		const TCHAR* strShaderFile, 	
										D3D10_SHADER_MACRO* pShaderMacros	= 0);		
	virtual HRESULT LoadShaderFile(		const TCHAR* strShaderFile, 	
										LPCSTR strVSEntryPoint, 
										LPCSTR strPSEntryPoint, 
										LPCSTR strShaderModel,
										D3D10_SHADER_MACRO* pShaderMacros	= 0);		
	virtual void	BindVertexBuffer(	ID3D11Buffer* pVertexBuffer=0, 
												UINT iStrides=0,							
												UINT iStartSlot = 0,
												UINT iNumBuffers = 1,																	
												UINT iOffsets = 0);

	virtual void	BindIndexBuffer(		ID3D11Buffer *pIndexBuffer=0,
												DXGI_FORMAT Format=DXGI_FORMAT_R32_UINT,
												UINT Offset=0 );

	virtual void	Draw(			UINT VertexCount,
										UINT StartVertexLocation=0);
	virtual void	DrawIndex(		UINT IndexCount, 
										UINT StartIndexLocation=0, 
										INT BaseVertexLocation=0);
	// multi thread
	virtual void	BindVertexBuffer( ID3D11DeviceContext* pContext,
										ID3D11Buffer* pVertexBuffer=0, 
												UINT iStrides=0,							
												UINT iStartSlot = 0,
												UINT iNumBuffers = 1,																	
												UINT iOffsets = 0  );
	virtual void	BindIndexBuffer(	ID3D11DeviceContext* pContext,		
										ID3D11Buffer *pIndexBuffer=0,
										DXGI_FORMAT Format=DXGI_FORMAT_R32_UINT,
										UINT Offset=0 );
	virtual void	Draw(	ID3D11DeviceContext* pContext,
							UINT VertexCount,
							UINT StartVertexLocation=0);
	virtual void	DrawIndex(	ID3D11DeviceContext* pContext,
								UINT IndexCount, 
								UINT StartIndexLocation=0, 
								INT BaseVertexLocation=0);
public:
	TRender(void);
	virtual ~TRender(void);
};
