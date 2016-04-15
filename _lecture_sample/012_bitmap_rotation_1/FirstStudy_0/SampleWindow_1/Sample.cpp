#include "Sample.h"



Sample::Sample()
{
}


Sample::~Sample()
{
}
int WINAPI wWinMain(
	HINSTANCE hInstatnce,
	HINSTANCE hPrevInstatnce,
	LPWSTR   lpCmdLine,
	int      nCmdShow)
{
	Sample win;
	if (win.SetWindow(hInstatnce) == true)
	{
		win.Run();
	}
	return 0;
}