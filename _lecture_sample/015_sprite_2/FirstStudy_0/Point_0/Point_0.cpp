// Point_0.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	//// n ����
	//pPoint = (int*)malloc(ibyte*10);
	//int **ppPoint = 0;
    return 0;
}

