#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>
#include <string.h>
#include "define.h"
#define START void main(int argc, char* argv[]) {
#define END }

A B C D E F G

TData g_Data[3] = {
	{ "aaaa", 20, 20, 20 },
	{ "bbb", 40, 20, 20 },
	{ "cc", 50, 20, 20 } };

bool WriteData(char* pFileName)
{
	if (pFileName == NULL) return false;
	FILE* fp = NULL;
	fp = fopen(pFileName, "wb");
	if (fp == NULL) return false;
	// 블록 단위 입출력
	fwrite(&g_Data, 3, sizeof(TData), fp);
	//for (int iData = 0; iData < 3; iData++)
	//{
	//	/*int iSize = strlen(g_Data[iData].szName);
	//	fwrite(&iSize, 1, sizeof(int), fp);
	//	fwrite(g_Data[iData].szName, 1, iSize, fp);
	//	fwrite(&g_Data[iData].kor, 1, sizeof(int), fp);
	//	fwrite(&g_Data[iData].eng, 1, sizeof(int), fp);
	//	fwrite(&g_Data[iData].mat, 1, sizeof(int), fp);*/
	//}

	fclose(fp);
	return true;
}
void ReadData(char* pfileName)
{
	FILE* fpRead = NULL;
	fpRead = fopen(pfileName, "r");
	if (fpRead == NULL) return;
	TData g_ReadData[3];
	memset(g_ReadData, 0, sizeof(TData) * 3);
	int iSize;
	
	while (1)
	{
		int iLen = fread(&g_ReadData, 3, sizeof(TData), fpRead);
		if (iLen ==0)
		{
			break;
		}
	}
	/*for (int iData = 0; iData < 3; iData++)
	{
		fread(&iSize, 1, sizeof(int), fpRead);
		fread(g_ReadData[iData].szName, 1, sizeof(char)*iSize, fpRead);
		fread(&g_ReadData[iData].kor, 1, sizeof(int), fpRead);
		fread(&g_ReadData[iData].eng, 1, sizeof(int), fpRead);
		fread(&g_ReadData[iData].mat, 1, sizeof(int), fpRead);
	}*/
	fclose(fpRead);
}
START
	if (argc != 2)
	{
		printf("\n%s", "사용법 : 실행파일 [opt] , opt:fileName");
		printf("\n%s", "예시  file_0.exe data.txt");
		return;
	}
	if (WriteData(argv[1]))
	{
		ReadData(argv[1]);
	}
	getchar();
END