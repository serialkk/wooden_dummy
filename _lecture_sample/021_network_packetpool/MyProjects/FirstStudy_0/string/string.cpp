// string.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	data.push_back(L"1ȫ�浿fdfds");
	data.push_back(L"2ȫ�浿fdfdfdfdfdsfsd");
	data.push_back(L"3ȫ�浿fdsfdasfsadfsdafsadfsdafa");
	data.push_back(L"4ȫ�浿aaaa");
	data.push_back(L"5ȫ�浿dfdfdsfdfdfsd");

	const TCHAR* pBuffer = data[0].c_str();
	Print(data[0].c_str());
	Print2(const_cast<TCHAR*>(data[0].c_str()));
	Print3(data[0].c_str());
    return 0;
}

