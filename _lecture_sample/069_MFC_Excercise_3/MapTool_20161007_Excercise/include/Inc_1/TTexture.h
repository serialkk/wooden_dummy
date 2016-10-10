#pragma once
#include "TBasisStd.h"

class TTexture
{
public:
	//--------------------------------------------------------------------------------------
	// �ؽ��� �ε� �� ���ҽ����� ����
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
