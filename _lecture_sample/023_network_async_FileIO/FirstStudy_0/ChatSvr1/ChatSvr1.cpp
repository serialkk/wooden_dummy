// Server_0.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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



