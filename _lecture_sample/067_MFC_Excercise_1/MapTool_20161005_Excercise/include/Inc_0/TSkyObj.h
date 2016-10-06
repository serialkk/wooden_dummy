#pragma once
#include "TBoxObj.h"
class TSkyObj : public TBoxObj
{
public:
	void SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	TSkyObj(void);
	virtual ~TSkyObj(void);
};
