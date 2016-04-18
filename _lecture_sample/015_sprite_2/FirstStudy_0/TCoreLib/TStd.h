#pragma once
#include <windows.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <list>
#include <string>
using namespace std;

template <class T> class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleton;
		return theSingleton;
	}
};