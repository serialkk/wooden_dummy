#pragma once
#include "TBasisStd.h"

class TTexture
{
public:
	//--------------------------------------------------------------------------------------
	// 텍스쳐 로딩 및 리소스버퍼 생성
	//--------------------------------------------------------------------------------------
	ID3D11ShaderResourceView*	m_pTextureRV;
	ID3D11SamplerState*			m_pSamplerState;
public:
	HRESULT						Load(ID3D11Device* pDevice,ID3D11DeviceContext*    pImmediateContext,TCHAR* strFilePath);
	bool						Apply(ID3D11DeviceContext*    pImmediateContext);
	bool						Release();

public:
	TTexture(void);
	~TTexture(void);
};
