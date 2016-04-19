#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>
struct TData
{
	char szName[10];
	int  kor;
	int  eng;
	int  mat;	
};
TData g_Data[3] = {
	{"aaa", 20, 20, 20},
	{ "bbb", 40, 20, 20 },
	{ "cc", 50, 20, 20 } };

bool WriteData(char* pFileName)
{
	if (pFileName == NULL) return false;
	FILE* fp = NULL;
	fp = fopen(pFileName, "w");
	if (fp == NULL) return false;
	fprintf(fp, "%s", "####### ���� ���� #####");
	for (int iData = 0; iData < 3; iData++)
	{
		fprintf(fp, "\n%s %d %d %d", g_Data[iData].szName,
			g_Data[iData].kor,
			g_Data[iData].eng,
			g_Data[iData].mat);
	}
	fclose(fp);
	return true;
}
void ReadData()
{
	FILE* fpRead = NULL;
	fpRead = fopen("data.txt", "r");
	if (fpRead == NULL) return;
	TData g_ReadData[3];
	memset(g_ReadData, 0, sizeof(TData) * 3);

	char szBuffer[256] = { 0, };
	int iData = 0;
	fgets(szBuffer, 256, fpRead);
	printf("%s", szBuffer);
	printf("\n%s\t%s\t%s\t%s\t%s\t%s",
		"����", "����", "����", "����", "����", "���");
	while(!feof(fpRead))
	{ 		
		fgets(szBuffer, 256, fpRead);
		sscanf(szBuffer, "%s %d %d %d", 
			g_ReadData[iData].szName,
			&g_ReadData[iData].kor,
			&g_ReadData[iData].eng,
			&g_ReadData[iData].mat);	

		int tot = g_ReadData[iData].kor + 
			g_ReadData[iData].eng + 
			g_ReadData[iData].mat;
		float ave = tot / 3.0f;
		printf("\n%s\t%d\t%d\t%d\t%d\t%-10.4f",
			g_ReadData[iData].szName,
			g_ReadData[iData].kor,
			g_ReadData[iData].eng,
			g_ReadData[iData].mat,
			tot, ave);

		iData++;
	}	
	fclose(fpRead);	
}
void main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("\n%s","���� : �������� [opt] , opt:fileName");
		printf("\n%s", "����  file_0.exe data.txt");
		return;
	}
	if (WriteData(argv[1]))
	{
		ReadData();
	}
	getchar();
}