// CreateFile_0.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <windows.h>
char* GetWtoM(WCHAR* data)
{
	char rData[2048] = { 0, };
	int iSize = 0;// ��ȯ�ϴ� ũ�Ⱑ ?
	iSize = WideCharToMultiByte(CP_ACP, 0, data, -1,
		0, 0, NULL, NULL);
	int iRet=WideCharToMultiByte(CP_ACP, 0, data, -1,
		rData, iSize, NULL, NULL);
	return rData;
}
int main()
{
	HANDLE hWriteFile = CreateFile(
			L"data.txt", 
			GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, 
			NULL );
	if (hWriteFile != NULL)
	{
		TCHAR buffer[] = L"game";
		DWORD dwSize = sizeof(buffer);
		DWORD dwWrite;
		BOOL iRet = WriteFile(hWriteFile, buffer, dwSize,
			&dwWrite, NULL);
		if (iRet == TRUE) { printf("���� ���!"); }
	}
	CloseHandle(hWriteFile);

	HANDLE hReadFile = CreateFile(
		L"data.txt",
		GENERIC_READ, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hReadFile != NULL)
	{
		TCHAR buffer[1024] = { 0, };
		DWORD dwSize = sizeof(buffer);
		DWORD dwRead;
		BOOL iRet = ReadFile(hReadFile, buffer, dwSize,
			&dwRead, NULL);
		if (iRet == TRUE) { 
			printf("%s", GetWtoM(buffer));
		}
	}
	CloseHandle(hReadFile);
    return 0;
}

