#pragma once
#include <windows.h>
#define T_START int WINAPI wWinMain(HINSTANCE hInstatnce,HINSTANCE hPrevInstatnce,LPWSTR   lpCmdLine,int      nCmdShow) {
#define T_END }
class TEngine
{
public:
	bool Init()
	{
		return true;
	}
public:
	TEngine();
	virtual ~TEngine();
};

