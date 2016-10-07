#pragma once
#include "TViewRT.h"
#include "TViewDS.h"
#include "TViewPort.h"
#include "TShape.h"
#include "TCamera.h"

class TMiniMap : public TCamera
{
public:
	TShape*								m_pPlaneShape;
	TViewRT*							m_pMiniMapRT;
	TViewDS*							m_pMiniMapDS;
	TViewPort							m_TextureVP;	

	ID3D11RenderTargetView*				m_pOldRT;
    ID3D11DepthStencilView*				m_pOldDS;
	UINT								m_nViewPorts;
	D3D11_VIEWPORT						m_vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];

public:
	ID3D11DepthStencilState*			m_pDepthStencilState;
	ID3D11BlendState*					m_pAlphaBlend;
	D3D11_PRIMITIVE_TOPOLOGY			m_PrimitiveType;
public:
	bool								Create(ID3D11Device* pd3dDevice,ID3D11DeviceContext*    pImmediateContext);
	bool								Frame();
	bool								Render(ID3D11DeviceContext*    pImmediateContext);
	bool								Release();
		
	bool								BeginRender(ID3D11DeviceContext*    pImmediateContext);
	bool								EndRender(ID3D11DeviceContext*    pImmediateContext);

	HRESULT								CreateResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext*    pImmediateContext, UINT iWidth, UINT iHeight);
	HRESULT								DeleteResource();
public:
	TMiniMap(void);
	virtual ~TMiniMap(void);
};
