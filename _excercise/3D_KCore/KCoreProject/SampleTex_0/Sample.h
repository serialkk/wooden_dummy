#pragma once
#include "Kcore.h"
struct SimpleVertex
{
	float x, y, z;
	float r, g, b, a;
	float u, v;
};
struct VS_CONSTANT_BUFFER
{
	float r, g, b, a;
};
class Sample : public KCore
{
public:
	KDXHelper			m_Object;
	VS_CONSTANT_BUFFER	m_cbData;
	
	ID3D11ShaderResourceView*   m_pTexSRV;
	ID3D11SamplerState*			m_pSamplerState;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	Sample();
	virtual ~Sample();
};

