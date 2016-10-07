#pragma once
#include "TBasisStd.h"

class TDxState
{
public:
	//--------------------------------------------------------------------------------------
	// 상태 변수
	//--------------------------------------------------------------------------------------	
	D3D11_PRIMITIVE_TOPOLOGY	m_PrimitiveType;
	D3D11_RASTERIZER_DESC		m_RasterizerDesc;
	D3D11_CULL_MODE				m_CullMode;
	D3D11_FILL_MODE				m_FillMode;
	D3D11_DEPTH_STENCIL_DESC	m_DepthStencilDesc; 

	// 동적 상태 객체
	ID3D11RasterizerState*      m_pRasterizerState;
	ID3D11DepthStencilState*	m_pDepthStencilState;	

	// 정적 상태 객체
	ID3D11RasterizerState* 		m_StateBackCullSolid;
	ID3D11RasterizerState*		m_StateFrontCullSolid;
	ID3D11RasterizerState* 		m_StateNoneCullSolid;	
	ID3D11RasterizerState* 		m_StateNoneCullWireFrame;
	ID3D11DepthStencilState*	m_pDepthEnableLessDSV;
	ID3D11DepthStencilState*	m_pDepthDisableLessDSV;
	ID3D11BlendState*           m_pSrcNoBlend;
	ID3D11BlendState*			m_pAlphaBlend;


	HRESULT Create(ID3D11Device* pDevice);
public:
	//--------------------------------------------------------------------------------------
	// 레스트라이져 상태 지정
	//--------------------------------------------------------------------------------------
	HRESULT		SetCullMode( ID3D11Device* pDevice, D3D11_CULL_MODE CullMode );
	HRESULT		SetFillMode( ID3D11Device* pDevice, D3D11_FILL_MODE FillMode );
	//--------------------------------------------------------------------------------------
	// 레스터라이저 상태값 지정
	//--------------------------------------------------------------------------------------
	HRESULT		SetRasterizerState( ID3D11Device* pDevice, 
									D3D11_CULL_MODE CullMode	= D3D11_CULL_FRONT, 
									D3D11_FILL_MODE d3dFillMode	= D3D11_FILL_SOLID );
	HRESULT		SetRasterizerState(ID3D11Device* pDevice, D3D11_RASTERIZER_DESC  RSDesc );
	//--------------------------------------------------------------------------------------
	// 프리미티브 유형 지정
	//--------------------------------------------------------------------------------------
	void		SetPrimitive( D3D11_PRIMITIVE_TOPOLOGY Primitive);
	void		SetPrimitive( int iPrimitive);
	//--------------------------------------------------------------------------------------
	// 레스터라이저 상태값 적용
	//--------------------------------------------------------------------------------------
	HRESULT		ApplyRasterizer(ID3D11Device* pDevice,ID3D11DeviceContext*   pImmediateContext);
	//--------------------------------------------------------------------------------------
	// 깊이 및 스텐실 버퍼 상태 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateDepthStencilState(	ID3D11Device* pDevice, 
											BOOL DepthEnable   = TRUE, 
											D3D11_COMPARISON_FUNC DepthFunc = D3D11_COMPARISON_LESS );
	HRESULT		CreateDepthStencilState(	ID3D11Device* pDevice, 
											D3D11_DEPTH_STENCIL_DESC dsd );
	HRESULT		ApplyDepthStencil(			ID3D11Device* pDevice, 
											ID3D11DeviceContext*   pImmediateContext,
											UINT iStencilRef = 0x00);
	//--------------------------------------------------------------------------------------
	// 블랜딩 상태
	//--------------------------------------------------------------------------------------

	HRESULT						CreateBlendState(ID3D11Device* pDevice);
	void						ApplyAlphaBlend(ID3D11DeviceContext*   pImmediateContext, const FLOAT fBlendFactor[] = 0, UINT iMask = 0xffffffff );
	void						ApplySrcNoBlend(ID3D11DeviceContext*   pImmediateContext, const FLOAT fBlendFactor[] = 0, UINT iMask = 0xffffffff );
	//--------------------------------------------------------------------------------------
	// 각종 상태 해제
	//--------------------------------------------------------------------------------------
	bool		Release();
public:
	TDxState(void);
	virtual ~TDxState(void);
};
static void ApplyRS(	ID3D11DeviceContext*   pImmediateContext, 
						ID3D11RasterizerState* pState )
{
	assert( pImmediateContext );
	pImmediateContext->RSSetState( pState );
}
static void ApplyDSS(	ID3D11DeviceContext*   pImmediateContext, 
							ID3D11DepthStencilState*	pDepthStencilState,
							UINT iRef = 0x01)
{
	assert( pImmediateContext );
	pImmediateContext->OMSetDepthStencilState( pDepthStencilState, iRef );	 	

};
static void ApplyBS(ID3D11DeviceContext*   pImmediateContext,
					ID3D11BlendState*      pBlendState,
					const FLOAT fBlendFactor[] = 0, 
					UINT iMask = 0xffffffff )
{
	assert( pImmediateContext );
	pImmediateContext->OMSetBlendState( pBlendState, fBlendFactor, iMask );
}