#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <vector>
#include <list>
#include "tprotocol.h"
#pragma comment(lib, "ws2_32.lib")
using namespace std;
#define MAX_RECV_BUFFER  4096
template <class T> class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleton;
		return theSingleton;
	}
};