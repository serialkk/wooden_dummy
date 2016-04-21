#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <tchar.h>
using namespace std;

#define SAFE_ZERO( p) { p = 0;}
#define SAFE_NEW( p, type ) { if(!p) { p = new type; } }
#define SAFE_DEL( p ) { if(p) { delete p; p = NULL;} }
#define SAFE_NEW_ARRAY( p, type, size ) { if(!p) { p = new type[size];} }
#define SAFE_DEL_ARRAY( p ) { if(p) { delete [] p; p = NULL;} }
