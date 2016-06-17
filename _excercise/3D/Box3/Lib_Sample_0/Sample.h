#pragma once
#pragma comment(lib,"TCoreDx_0.lib")
#include "TDxStd.h"
#include "TDevice.h"
#include <D3DX10math.h>



class Sample : public TDevice
{
	ConstantBuffer cb, cb_game;

	ID3D11VertexShader*     g_pVertexShader = NULL;
	ID3D11PixelShader*      g_pPixelShader = NULL;
	ID3D11InputLayout*      g_pVertexLayout = NULL;
	ID3D11Buffer*           g_pVertexBuffer = NULL;
	//아래 2개 인터페이스가 추가가됨.(필요한 버퍼: 정점, 인덱스, 상수 버퍼.)
	ID3D11Buffer*           g_pIndexBuffer = NULL; //인덱스 버퍼
	ID3D11Buffer*           g_pConstantBuffer = NULL; //상수 버퍼

	//TObject				m_Object[MAX_OBJECT];
	//void    SetRect(RECT& rt, int iObj);
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	Sample();
	virtual ~Sample();
};

