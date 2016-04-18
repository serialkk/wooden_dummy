#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
#include <iostream>
#include <cstdio>
using namespace std;

#ifndef _DEBUG
	void main()
	{		
		int iValue;
		float fValue;
		cout << "정수 입력";
		cin >> iValue;
		cin >> fValue;		
		cout << iValue << " " << fValue;
		printf("디버그 버전");
	}
#else
	void main()
	{
		int iValue;
		float fValue =3.14f;
		char  array[7];// = "abcdef";
		char  ch0,ch1;
		
		// ; 'scanf': This function or variable
		//may be unsafe.
		// 버퍼오버런
		//Consider using scanf_s instead.
		//To disable deprecation,
		//use _CRT_SECURE_NO_WARNINGS.
		//See online help for details.
		printf("\n문자 입력0");
		scanf("%c", &ch0);
		
		//while (getchar() != '\n');
		char ch;
		while(ch= cin.get() != '\n' &&
			   ch != EOF);

		printf("\n문자 입력1");
		scanf("%c", &ch1);
		printf("\n정수 입력");
		scanf("%d", &iValue);
		printf("\n실수 입력");
		scanf("%f", &fValue);
		printf("\n문자열 입력");
		scanf("%s", array);
		printf("\n%c %d %-10.2f",ch0, iValue, fValue);		
		printf("\n%s",array);
		printf("릴리즈 버전");
	}
#endif

