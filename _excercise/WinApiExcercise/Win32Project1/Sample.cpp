#include <windows.h>
#include <tchar.h>
#include "Sample.h"


bool Sample::Init()
{
	//m_Timer.Init();
	return true;
}
bool Sample::Frame()
{
	//m_Timer.Frame();
	return true;
}
bool Sample::Render()
{
	//m_Timer.Render();
	return true;
}
bool Sample::Release()
{
	//m_Timer.Release();
	return true;
}



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdSHow)
{
	Sample win;
	if (win.SetWindow(hInstance) == true)
	{
		win.Run();
	}
	return 0;
}

Sample::Sample() {}
Sample::~Sample() {}