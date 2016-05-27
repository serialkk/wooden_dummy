#include "Tiocp.h"

void main()
{
	Tiocp   iocp;
	if (!iocp.Init())
	{
		return;
	}
	iocp.Run();
}