// string.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef basic_string<TCHAR> TStr;
typedef std::vector<TStr>   TStrArray;

void Print(const TCHAR* pData)
{
	cout << pData;
}
void Print2( TCHAR* pData)
{
	cout << pData;
}
void Print3(TStr pData)
{
	cout << pData.c_str();
}
int main()
{		
	std::string buf1 = "kgca";
	std::string buf2 = "KGCA";
	if (buf1 == buf2)
	{

	}
	char buffer[256] = { 0 };
	strcpy(buffer, buf1.c_str());


	TStrArray data;
	data.push_back(L"1홍길동fdfds");
	data.push_back(L"2홍길동fdfdfdfdfdsfsd");
	data.push_back(L"3홍길동fdsfdasfsadfsdafsadfsdafa");
	data.push_back(L"4홍길동aaaa");
	data.push_back(L"5홍길동dfdfdsfdfdfsd");

	const TCHAR* pBuffer = data[0].c_str();
	Print(data[0].c_str());
	Print2(const_cast<TCHAR*>(data[0].c_str()));
	Print3(data[0].c_str());
    return 0;
}

