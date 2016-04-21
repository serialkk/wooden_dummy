// Point_0.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>

int main()
{
	void* pPointVoid = 0;
	int i = 100;
	int* pPoint = &i;
	printf("%d", *pPoint);
	//int ibyte = sizeof(int);
	//int iData[10];
	//// n 개수
	//pPoint = (int*)malloc(ibyte*10);
	//int **ppPoint = 0;
    return 0;
}

