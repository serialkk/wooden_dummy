#pragma once
#include "TBasisStd.h"
#include "TMesh.h"
#include "TShader.h"
#include "TDxBuffer.h"

class TRender
{
public:
	ID3D11Device*				m_pd3dDevice;	
	ID3D11DeviceContext*		m_pd3dImmediateContext;
	ID3D11CommandList*          m_pd3dCommandList;
	TShader*					m_pShader;
	int							m_iPrimitiveType;
	int							m_iVertexSize;
	int							m_iIndexSize;
	bool				m_bDynamicCB; // 로칼 상수버퍼 사용 유무
	void				ApplyCB(bool bUse = false) { m_bDynamicCB = bUse; };
	cbChangesEveryFrame			m_cbEveryFrame;
	cbChangeOnResize			m_cbOnResize;
	TDxBuffer					m_EveryFrameCBuffer;
	TDxBuffer					m_OnResizeCBuffer;
	ID3D11Buffer*				m_pGlobalEveryFrameCBuffer; // 상수버퍼
	ID3D11Buffer*				m_pGlobalOnResizeCBuffer; // 상수버퍼

	HRESULT					CreateConstantBuffer(D3D11_USAGE type = D3D11_USAGE_DEFAULT);
	void					SetEveryFrameCBuffer(ID3D11DeviceContext* pImmediateContext, D3DXMATRIX& matWorld, D3DXMATRIX& matView);
	void					SetOnResizeCBuffer(ID3D11DeviceContext* pImmediateContext, D3DXMATRIX& matProj);
	bool					SetupRender(ID3D11DeviceContext*	pImmediateContext,
		ID3D11Buffer* pCB0 = 0,
		ID3D11Buffer* pCB1 = 0)  ;
	TInputLayout		m_InputLayout;
	HRESULT				SetInputLayout(ID3D11Device* pd3dDevice, D3D11_INPUT_ELEMENT_DESC* pLayout = NULL, UINT numElements = 4);

public:
	virtual void	SetContext(ID3D11DeviceContext* pd3dImmediateContext){m_pd3dImmediateContext = pd3dImmediateContext;};
	virtual TShader*  LoadShaderFile(	const TCHAR* strShaderFile, 	
										LPCSTR strVSEntryPoint=0, 
										LPCSTR strPSEntryPoint=0, 
										LPCSTR strShaderModel=0,
										D3D10_SHADER_MACRO* pShaderMacros	= 0);		
	virtual TShader* 	LoadShader(	ID3D11Device* pd3dDevice,
										TCHAR* pLoadShaderFile,
										CHAR* pEntryPoint, 
										CHAR* pCompiler,
										STAGE_TYPE type = t_VS);
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

	virtual void	Draw(	ID3D11DeviceContext* pContext, TShader* pShader,
							UINT VertexCount,
							UINT StartVertexLocation=0);
	virtual void	DrawIndex(	ID3D11DeviceContext* pContext, TShader* pShader,
								UINT IndexCount, 
								UINT StartIndexLocation=0, 
								INT BaseVertexLocation=0);
	virtual HRESULT	SetCommmandList(ID3D11DeviceContext* pContext, TMesh* pSubMesh, bool bSave=false );
	virtual void	ExecuteCommandList(ID3D11DeviceContext* pContext,TMesh* pSubMesh, bool bClear=true );
public:
	TRender(void);
	virtual ~TRender(void);
};
