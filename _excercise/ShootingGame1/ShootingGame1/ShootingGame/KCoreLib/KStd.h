#pragma once
#include <windows.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <list>
#include <string>
using namespace std;

struct KRect
{
	int   x, y;
	int   w, h;
};
template <class T> class KSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleton;
		return theSingleton;
	}
};