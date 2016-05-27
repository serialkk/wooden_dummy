#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <map>
#include <string>
using namespace std;
#pragma comment( lib, "ws2_32.lib")

template<class T> class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
};
// md  "../../include/TBasisServer"
// copy "*.h" "../../include/TBasisServer"
// copy "*.lib" "../../lib"


