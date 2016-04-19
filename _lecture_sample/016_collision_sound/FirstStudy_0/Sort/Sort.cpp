// Sort.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>

void SetData(int item[], int iCount)
{
	time_t tmp = clock();
	unsigned int iTick = 0;// rand();
	srand((unsigned int)time(&tmp));
	for (int i = 0; i < iCount; i++)
	{
		item[i] = (iTick + rand() ) % iCount;
	}
};
bool Swap(int * a, int * b)
{
	if ((*a) > (*b))
	{
		int t = *a;
		*a = *b;
		*b = t;
		return true;
	}
	return false;
}
void SelectionSort(int item[], int iCount)
{
	for (int a = 0; a < iCount; a++)
	{
		bool bFlag = false;
		for (int b = a + 1; b < iCount; b++)
		{
			if (Swap(&item[a], &item[b]))
			{
				bFlag = true;
			}
		}if (bFlag == false) break;
	}
}
void BubbleSort(int item[], int iCount)
{
	for (int a = 0; a < iCount-1; a++)
	{
		bool bFlag = false;
		for (int b = 0; b < iCount-a-1; b++)
		{
			if (Swap(&item[b], &item[b + 1]))
			{
				bFlag = true;
			}
		}
		if (bFlag == false)
		{
			break;
		}
	}
}
void InsertionSort( int item[], 
					int iCount,
					int iStart=1,
					int iStep=1)
{
	for (int a = iStart; a < iCount; a+= iStep)
	{
		int tmp = item[a];
		int b = a- iStep;
		while ( b >=0 && item[b] > tmp)
		{
			item[b+ iStep] = item[b];
			b-= iStep;
		}
		item[b+ iStep] = tmp;
	}
}
void ShellSort(int item[], int iCount)
{
	int k = iCount;
	while (k > 1)
	{
		k = k / 2;
		// 부분정렬
		for (int s = 0; s < k; s++)
		{
			InsertionSort(item, iCount, s, k);
		}
	}
}
int Partition(int item[], int iBegin, int iEnd)
{
	int left, right, iPivot;
	left = iBegin + 1;
	right = iEnd;
	iPivot = iBegin;
	while (left <= right)
	{
		while (item[left] <= item[iPivot] &&
			    left <= iEnd) left++;
		while (item[right] >= item[iPivot] &&
				right >= iBegin+1) right--;
		if (left <= right)
		{
			Swap(&item[left], &item[right]);
		}
	}
	// 전환
	Swap(&item[iBegin], &item[right]);
	return right;
}
void QuickSort(int item[], int iBegin, int iEnd)
{
	if( iBegin < iEnd)
	{
		int X = Partition(item, iBegin, iEnd);
		QuickSort(item, iBegin, X-1);
		QuickSort(item, X+1, iEnd);
	}
}
void DataPrint(int item[], int iCount)
{
	return;
	for (int i = 0; i < 1000; i++)
	{
		printf(" %d", item[i]);
	}
}
#define MAX_CNT 50000
int main()
{
	int item[MAX_CNT];
	
	SetData(item, MAX_CNT);
	// 선택 정렬
	time_t stmp = clock();
	SelectionSort(item, MAX_CNT);
	time_t etmp = clock();
	printf("\n%s:%8.3f[%ld] ", "선택정렬",
		(etmp - stmp) / (double)CLK_TCK,
		etmp - stmp);
	DataPrint(item, MAX_CNT);

	//// 거품 정렬
	//SetData(item, MAX_CNT);	
	//stmp = clock();
	//BubbleSort(item, MAX_CNT);
	//etmp = clock();
	//printf("\n%s:%8.3f[%ld] ", "거품정렬",
	//	(etmp - stmp) / (double)CLK_TCK,
	//	etmp - stmp);
	//DataPrint(item, MAX_CNT);

	// 삽입 정렬
	SetData(item, MAX_CNT);
	stmp = clock();
	InsertionSort(item, MAX_CNT);
	etmp = clock();
	printf("\n%s:%8.3f[%ld] ", "삽입정렬",
		(etmp - stmp) / (double)CLK_TCK,
		etmp - stmp);
	DataPrint(item, MAX_CNT);

	// 셀 정렬
	SetData(item, MAX_CNT);
	stmp = clock();
	ShellSort(item, MAX_CNT);
	etmp = clock();
	printf("\n%s:%8.3f[%ld] ", "셀 정렬",
		(etmp - stmp) / (double)CLK_TCK,
		etmp - stmp);
	DataPrint(item, MAX_CNT);

	// 퀵 정렬
	SetData(item, MAX_CNT);
	stmp = clock();
	QuickSort(item, 0, MAX_CNT-1);
	etmp = clock();
	printf("\n%s:%8.3f[%ld] ", "퀵 정렬",
		(etmp - stmp) / (double)CLK_TCK,
		etmp - stmp);
	DataPrint(item, MAX_CNT);
    return 0;
}

