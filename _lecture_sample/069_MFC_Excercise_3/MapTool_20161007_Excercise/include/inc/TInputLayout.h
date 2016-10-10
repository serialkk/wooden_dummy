#pragma once
#include "TBasisStd.h"

class TInputLayout
{
public:
	ID3D11InputLayout*      m_pVertexLayout;
	static ComPtr<ID3D11InputLayout>  g_pPNCT;
public:
	static bool    Set(ID3D11Device* pDevice);
	static HRESULT Bind(ID3D11Device* pDevice,
		D3D11_INPUT_ELEMENT_DESC* pLayout,
		UINT numElements,
		ID3DBlob* pVSBuf,
		ID3D11InputLayout** ppGetVertexLayout = NULL);

	HRESULT Create(		ID3D11Device* pDevice,
						D3D11_INPUT_ELEMENT_DESC* pLayout,
						UINT numElements,
						ID3DBlob* pVSBuf,
						ID3D11InputLayout** ppGetVertexLayout = NULL );
	void				Apply(ID3D11DeviceContext*    pImmediateContext);
	bool				Release();
public:
	TInputLayout(void);
	virtual ~TInputLayout(void);
};
