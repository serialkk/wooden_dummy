// Server_0.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "TChatSvr.h"
void main()
{
	I_CharSvr.Init();
	I_CharSvr.Set(10000);
	I_CharSvr.Run();
	I_CharSvr.Release();
}



