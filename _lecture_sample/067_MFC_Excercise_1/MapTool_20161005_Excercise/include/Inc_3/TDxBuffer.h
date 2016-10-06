#pragma once
#include "TBasisStd.h"

#define COUNTOF(a) ( sizeof( a ) / sizeof( ( a )[0] ) )

struct cbChangesEveryFrame
{
	D3DXMATRIX   matWorld;
	D3DXMATRIX   matView;
};
struct cbChangeOnResize
{
	D3DXMATRIX   matProj;
};
struct cbNeverChanges
{	
};	

class TDxBuffer
{
public:
	UINT					m_iCount;
	UINT					m_iBindFlags;
	UINT					m_iSize;
	D3D11_BUFFER_DESC		m_BufferDesc;
	D3D11_SUBRESOURCE_DATA  m_SubResourceData;
public:
	ID3D11Buffer*			m_pBuffer;	

public:
	HRESULT				Create(	ID3D11Device* pDevice,
								UINT iSize, 
								UINT iCounter,
								void* pPoint, 
								UINT  BindFlags,
								D3D11_USAGE uSage = D3D11_USAGE_DEFAULT,
								ID3D11Buffer** ppGetBuffer=0 );
	bool				Release();
	void				Apply(ID3D11DeviceContext* pd3dDeviceContext);
	
public:
	TDxBuffer(void);
	virtual ~TDxBuffer(void);
};
