#pragma once
#include "TBoxObject.h"

class TSphereObject : public TBoxObject
{
public:
	ID3DX11EffectTechnique*		m_pTechniqueFresnel;
	ID3DX11EffectTechnique*		m_pTechniqueRefraction;
	ID3DX11EffectTechnique*		m_techniqueCube;
	ID3DX11EffectTechnique*		m_techniqueShadowVolume;
	ID3DX11EffectMatrixVariable* m_matViewCubeVariable;
	ID3DX11EffectConstantBuffer* m_pCBVariable;

	float			m_fRadius;
	D3DXVECTOR3		m_vCenter;
	D3DXVECTOR4		m_vAmbientColor;
	D3DXMATRIX		m_matViewCube[6];
	int				m_iRenderPass;
public:
	bool			Update(ID3D11DeviceContext*	pImmediateContext);
	bool			Init();
	bool			Render(ID3D11DeviceContext*	pImmediateContext);
	void			GetEffectVariable();
	HRESULT			SetConstantBuffer(ID3D11Buffer*	pConstantBuffer);
	void			SetFillMode( bool bWireFrame=false );
public:
	TSphereObject()	
	{
		m_fRadius		= 1.0f;
		m_iPreLodCnt	= 9;
		m_vCenter		= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		m_vAmbientColor	= D3DXVECTOR4( 0.1f, 0.1f, 0.2f, 1.0f );
		m_pTechniqueFresnel = NULL;
		m_iRenderPass	= 0;
	};
	virtual ~TSphereObject();
};
