#pragma once
#include "TSphereObject.h"
class TSkyObject : public TSphereObject
{
public:
	ID3D11DeviceContext*        g_pd3dPerChunkDeferredContext;
public:
	void	SetMatrix( const D3DXMATRIX* pWorld, const D3DXMATRIX* pView, const D3DXMATRIX* pProj );
public:
	TSkyObject(void);
	virtual ~TSkyObject(void);
};
