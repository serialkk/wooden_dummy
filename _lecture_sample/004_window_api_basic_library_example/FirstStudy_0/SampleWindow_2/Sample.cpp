#include "Sample.h"
bool Sample::Init()
{
	m_Timer.Init();
	return true;
}
bool Sample::Frame()
{
	m_Timer.Frame();
	return true;
}
bool Sample::Render()
{
	m_Timer.Render();
	return true;
}
bool Sample::Release()
{
	m_Timer.Release();
	return true;
}

int WINAPI wWinMain(
	HINSTANCE hInstatnce,
	HINSTANCE hPrevInstatnce,
	LPWSTR   lpCmdLine,
	int      nCmdShow)
{
	Sample win;
	//win.SetRect(1024, 768);
	if (win.SetWindow(hInstatnce) == true)
	{
		win.Run();
	}
	return 0;
}
Sample::Sample()
{
}


Sample::~Sample()
{
}
