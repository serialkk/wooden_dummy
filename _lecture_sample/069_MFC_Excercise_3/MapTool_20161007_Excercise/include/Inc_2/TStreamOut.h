#pragma once
#include "TBasisStd.h"

class TStreamOut
{
public:	
	ID3D11Buffer*               m_pDrawFrom;
	ID3D11Buffer*               m_pStreamTo;
	ID3D11Buffer*				GetDrawBuffer();
public:
	HRESULT		CreateStreams( D3D11_BUFFER_DESC vbdesc, ID3D11Device* pd3dDevice);
	HRESULT		Begin( ID3D11DeviceContext*    pImmediateContext );
	void		End( ID3D11DeviceContext*    pImmediateContext );
	bool		Release();
public:
	TStreamOut(void);
	virtual ~TStreamOut(void);
};

