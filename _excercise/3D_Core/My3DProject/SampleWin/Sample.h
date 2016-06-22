#pragma once
#include "Tcore.h"
#include "TWrite.h"

class Sample : public TCore
{
public:
	TWrite		m_Font;
	ID3D11VertexShader*     g_pVertexShader;
	ID3D11PixelShader*      g_pPixelShader;
	ID3D11InputLayout*      g_pVertexLayout;
	ID3D11Buffer*           g_pVertexBuffer;
	ID3D11Buffer*           g_pVBLine;
	ID3D11Buffer*           g_pIndexBuffer;
	ID3D11Buffer*           g_pConstantBuffer;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	bool   ResizeClient(UINT iWidth, UINT iHeight);
	Sample();
	virtual ~Sample();
};

