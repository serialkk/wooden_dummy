#pragma once
#include "TShape.h"

class TNormalMap
{
public:
	DWORD EncodeVectorAsDWORDColor(D3DXVECTOR3* vVector);
	void TNormalMap::CreateTangentSpaceVectors(D3DXVECTOR3 *v0,
		D3DXVECTOR3 *v1,
		D3DXVECTOR3 *v2,
		D3DXVECTOR2 uv0,
		D3DXVECTOR2 uv1,
		D3DXVECTOR2 uv2,
		D3DXVECTOR3 *vTangent,
		D3DXVECTOR3 *vBiNormal,
		D3DXVECTOR3 *vNormal);
	void CreateTangentSpaceVectors(D3DXVECTOR3 *v1,
		D3DXVECTOR3 *v2,
		D3DXVECTOR3 *v3,
		float v1u, float v1v,
		float v2u, float v2v,
		float v3u, float v3v,
		D3DXVECTOR3 *vTangent,
		D3DXVECTOR3 *vBiNormal,
		D3DXVECTOR3 *vNormal);
	void Release();
public:
	TNormalMap(void);
	~TNormalMap(void);
};
