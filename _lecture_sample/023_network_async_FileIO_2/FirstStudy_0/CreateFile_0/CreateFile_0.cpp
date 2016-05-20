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
	DWORD dwValue;
	OVERLAPPED  ov = { 0, };
	OVERLAPPED  Read_ov = { 0, };
	DWORD dwSize;
	DWORD dwWrite;
	DWORD dwRead;
	BOOL iRet;

	TCHAR buffer[26] = { 0, };
	for (int i = 0; i < 26; i++)
	{
		buffer[i] = 'a' + i;
	}
	TCHAR buffer2[26] = { 0, };
	for (int i = 0; i < 26; i++)
	{
		buffer2[i] = 'A' + i;
	}
	dwSize = sizeof(buffer);
	HANDLE hWriteFile = CreateFile(
			L"data.txt", 
			GENERIC_WRITE | GENERIC_READ, 0, NULL,
			CREATE_ALWAYS,
			FILE_FLAG_OVERLAPPED,
			//FILE_ATTRIBUTE_NORMAL, 
			NULL );
#pragma region WriteFile
	if (hWriteFile != NULL)
	{
		
		ov.hEvent = NULL;// CreateEvent(NULL, FALSE, FALSE, NULL);

		
		// ���� ��� -> Ŀ�� ��� ���
		// Ŀ�� ��� -> ������� ����
		// �񵿱� �۾� ����� ť�� ������ �����ȴ�.
		
		iRet = WriteFile(hWriteFile, buffer, dwSize,
			&dwWrite, &ov);
		if (iRet == FALSE)
		{
			dwValue = GetLastError();
			// �������̴�.
			if (dwValue == ERROR_IO_PENDING)
			{
				// ����
			}
			else
			{
				exit(1);
			}
		
		}
		if (iRet == TRUE) 
		{
			printf("���� ���!"); 
			exit(1);
		}
	}
	//���� �۾� �� ������ ������ �۾��� �� �� �ִ�.
	//WaitForSingleObject(ov.hEvent, INFINITE);
	// �񵿱� �۾��� ��� Ȯ��	
	if (GetOverlappedResult(hWriteFile, &ov,
									&dwValue, TRUE)
		== FALSE )
	{
		exit(1);
	}
	//CloseHandle(hWriteFile);
	//CloseHandle(hWriteFile);
	//     4 byte            4byte
	// 0000000000000001 000000000000000000
	//    hightpart        lowpart
	//  quadpart == 1024 * 10;
	// hight part = 1;
	// lowpart = 0;
	LARGE_INTEGER  iLarge = { 0, };
	iLarge.QuadPart += sizeof(TCHAR) * 26;
	ov.Offset = iLarge.LowPart;
	ov.OffsetHigh = iLarge.HighPart;

	iRet = WriteFile(hWriteFile, buffer2, dwSize,
		&dwWrite, &ov);

	if (iRet == FALSE)
	{
		dwValue = GetLastError();
		// �������̴�.
		if (dwValue == ERROR_IO_PENDING)
		{
			// ����
		}
		else
		{
			exit(1);
		}

	}
	if (iRet == TRUE)
	{
		printf("���� ���!");
		exit(1);
	}

	//���� �۾� �� ������ ������ �۾��� �� �� �ִ�.
	WaitForSingleObject(ov.hEvent, INFINITE);
	// �񵿱� �۾��� ��� Ȯ��	
	if (GetOverlappedResult(hWriteFile, &ov,
		&dwValue, TRUE)
		== FALSE)
	{
		exit(1);
	}

	TCHAR  readBuffer[MAX_PATH] = { 0, };
	iLarge.QuadPart = 0;
	ov.Offset = iLarge.LowPart;
	ov.OffsetHigh = iLarge.HighPart;

	iRet = ReadFile(hWriteFile, readBuffer, 6,
		&dwRead, &ov);
	if (iRet == FALSE)
	{
		dwValue = GetLastError();
		// �������̴�.
		if (dwValue == ERROR_IO_PENDING)
		{
			// ����
		}
		else
		{
			exit(1);
		}

	}
	if (iRet == TRUE)
	{
		printf("���� ���!");
		exit(1);
	}

	//���� �۾� �� ������ ������ �۾��� �� �� �ִ�.
	WaitForSingleObject(ov.hEvent, INFINITE);
	// �񵿱� �۾��� ��� Ȯ��	
	if (GetOverlappedResult(hWriteFile, &ov,
		&dwValue, TRUE)
		== FALSE)
	{
		exit(1);
	}
	
	if (ov.hEvent != NULL)
	{
		CloseHandle(ov.hEvent);
	}
	CloseHandle(hWriteFile);

#pragma endregion

	TCHAR* pBuffer = 0;
	LARGE_INTEGER filesize;
	HANDLE hReadFile = CreateFile(
		L"a.exe",
		GENERIC_READ, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL| FILE_FLAG_OVERLAPPED,
		NULL);
	if (hReadFile != NULL)
	{
		GetFileSizeEx(hReadFile, &filesize);
		pBuffer = new TCHAR[filesize.QuadPart];
		if (pBuffer == NULL)
		{
			CloseHandle(hReadFile);
			return 0;
		}
	}
	Read_ov.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	dwSize = filesize.QuadPart;
	iRet = ReadFile(hReadFile, pBuffer, dwSize,
			&dwRead, &Read_ov);	
	if (iRet == FALSE)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			printf("\continue");
		}
	}
	if (iRet == TRUE)
	{
		return 0;
	}
	WaitForSingleObject(Read_ov.hEvent, INFINITE);
	// �񵿱� �۾��� ��� Ȯ��	
	if (GetOverlappedResult(hWriteFile, &Read_ov,
		&dwValue, TRUE)
		== FALSE)
	{
		exit(1);
	}

	while (1)
	{				
		DWORD dwRet = WaitForSingleObject(Read_ov.hEvent, 0);
		if( dwRet == WAIT_OBJECT_0)
		{
			DWORD ret = GetOverlappedResult(
				hReadFile, &Read_ov,
				&dwValue, FALSE);
			if (dwValue >= dwSize)
			{
				break;
			}
		}
		else if (dwRet == WAIT_TIMEOUT)
		{
			static int iCnt = 0;
			// �߰� ���� Ȯ��
			dwRet = GetOverlappedResult(hReadFile, 
				&Read_ov, &dwRead, FALSE);
			if (dwRet == FALSE)
			{
				if (GetLastError() == ERROR_IO_INCOMPLETE)
				{
					
					printf("\n%ld", iCnt++);
				}
			}
			else
			{
				printf("\n%ld", iCnt++);
			}			
		}
		else
		{
			//  ����
			break;
		}
	}
	SetFilePointer(pBuffer, 0, 0, FILE_BEGIN);
	delete[] pBuffer;
	CloseHandle(hReadFile);
    return 0;
}

