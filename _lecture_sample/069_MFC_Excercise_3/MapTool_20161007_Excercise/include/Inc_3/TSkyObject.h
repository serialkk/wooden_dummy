#pragma once
#include "TSphereObject.h"
class TSkyObject : public TSphereObject
{
public:
	ID3D11DeviceContext*        g_pd3dPerChunkDeferredContext;
public:
	void	SetMatrix( const D3DXMATRIX* pWorld, const D3DXMATRIX* pView, const D3DXMATRIX* pProj );
	void	GetEffectVariable();
	bool	Render();
	bool	Render(ID3D11DeviceContext* pContext);
public:
	TSkyObject(void);
	virtual ~TSkyObject(void);
};
