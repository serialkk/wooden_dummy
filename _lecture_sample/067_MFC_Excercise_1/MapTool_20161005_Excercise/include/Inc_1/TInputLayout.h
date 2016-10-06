#pragma once
#include "TBasisStd.h"
#include "TShader.h"

class TInputLayout
{
public:
	ID3D11InputLayout*      m_pVertexLayout;
public:
	HRESULT Create(		ID3D11Device* pDevice,
						D3D11_INPUT_ELEMENT_DESC* pLayout,
						UINT numElements,
						ID3DX11EffectTechnique**  ppSetTechnique, 
						ID3D11InputLayout** ppGetVertexLayout = NULL  );

	HRESULT Create(		ID3D11Device* pDevice,
						D3D11_INPUT_ELEMENT_DESC* pLayout,
						UINT numElements,
						ID3DBlob* pVSBuf,
						ID3D11InputLayout** ppGetVertexLayout = NULL );
	void				Apply(ID3D11DeviceContext*    pImmediateContext);
	bool				Release();
public:
	TInputLayout(void);
	~TInputLayout(void);
};
