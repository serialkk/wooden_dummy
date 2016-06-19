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
	//�Ʒ� 2�� �������̽��� �߰�����.(�ʿ��� ����: ����, �ε���, ��� ����.)
	ID3D11Buffer*           g_pIndexBuffer = NULL; //�ε��� ����
	ID3D11Buffer*           g_pConstantBuffer = NULL; //��� ����

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

