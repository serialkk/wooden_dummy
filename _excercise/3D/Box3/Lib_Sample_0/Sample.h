#pragma once
#pragma comment(lib,"TCoreDx_0.lib")
#include "TDxStd.h"
#include "TDevice.h"
#include <D3DX10math.h>



class Sample : public TDevice
{
	ConstantBuffer cb, cb_game;

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

