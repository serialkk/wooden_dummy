// CreateFile_0.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
char* GetWtoM(WCHAR* data)
{
	char rData[2048] = { 0, };
	int iSize = 0;// 변환하는 크기가 ?
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

		
		// 유저 모드 -> 커널 모드 명령
		// 커널 모드 -> 유저모드 통지
		// 비동기 작업 경과의 큐가 별도로 관리된다.
		
		iRet = WriteFile(hWriteFile, buffer, dwSize,
			&dwWrite, &ov);
		if (iRet == FALSE)
		{
			dwValue = GetLastError();
			// 진행중이다.
			if (dwValue == ERROR_IO_PENDING)
			{
				// 정상
			}
			else
			{
				exit(1);
			}
		
		}
		if (iRet == TRUE) 
		{
			printf("정상 출력!"); 
			exit(1);
		}
	}
	//뭔가 작업 주 스레드 별도의 작업을 할 수 있다.
	//WaitForSingleObject(ov.hEvent, INFINITE);
	// 비동기 작업의 결과 확인	
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
		// 진행중이다.
		if (dwValue == ERROR_IO_PENDING)
		{
			// 정상
		}
		else
		{
			exit(1);
		}

	}
	if (iRet == TRUE)
	{
		printf("정상 출력!");
		exit(1);
	}

	//뭔가 작업 주 스레드 별도의 작업을 할 수 있다.
	WaitForSingleObject(ov.hEvent, INFINITE);
	// 비동기 작업의 결과 확인	
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
		// 진행중이다.
		if (dwValue == ERROR_IO_PENDING)
		{
			// 정상
		}
		else
		{
			exit(1);
		}

	}
	if (iRet == TRUE)
	{
		printf("정상 출력!");
		exit(1);
	}

	//뭔가 작업 주 스레드 별도의 작업을 할 수 있다.
	WaitForSingleObject(ov.hEvent, INFINITE);
	// 비동기 작업의 결과 확인	
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
	// 비동기 작업의 결과 확인	
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
			// 중간 과정 확인
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
			//  오류
			break;
		}
	}
	SetFilePointer(pBuffer, 0, 0, FILE_BEGIN);
	delete[] pBuffer;
	CloseHandle(hReadFile);
    return 0;
}

