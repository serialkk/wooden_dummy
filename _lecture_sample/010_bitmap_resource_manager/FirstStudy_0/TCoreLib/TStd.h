#pragma once
#include <windows.h>
#include <tchar.h>

template <class T> class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleton;
		return theSingleton;
	}
};