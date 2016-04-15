#include "TManager.h"

void main()
{
	/*TStudent* std[100];
	TManager mgr;
	for (100)
	{
		std[i] = new TStudent(10, 10, 10);
		mgr.Add(std[i]);
	}*/
	TManager mgr;
	mgr.InputData(10);
	mgr.ShowData(mgr.Find(8));
	mgr.ShowData(mgr.Find(_T("CYXY")));
	mgr.Sort();
	mgr.ShowData();
	mgr.Release();
}