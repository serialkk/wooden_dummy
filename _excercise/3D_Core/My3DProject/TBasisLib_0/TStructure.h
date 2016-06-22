#pragma once

#include "TDefine.h"

namespace TBASIS_BASE {

struct TBASIS_INPUT_MAP
{
	bool bUpKey;
	bool bDownKey;
	bool bLeftKey;
	bool bRightKey;
	
	bool bWKey;
	bool bSKey;	
	bool bAKey;
	bool bDKey;	
	bool bQKey;
	bool bEKey;	
	
	bool bLeftClick;
	bool bRightClick;
	bool bMiddleClick;

	bool bExit;
	bool bSpace; // 카메라의 이동가속도를 증가시킨다.

	int  iMouseValue[3];

	bool bFullScreen;
	bool bChangeFillMode;
	bool bChangePrimitive;
	bool bChangeCullMode;
	bool bChangeCameraType;
};
extern TBASIS_INPUT_MAP g_InputData;
extern float			g_fSecPerFrame;

}