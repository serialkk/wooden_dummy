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
		cout << "���� �Է�";
		cin >> iValue;
		cin >> fValue;		
		cout << iValue << " " << fValue;
		printf("����� ����");
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
		// ���ۿ�����
		//Consider using scanf_s instead.
		//To disable deprecation,
		//use _CRT_SECURE_NO_WARNINGS.
		//See online help for details.
		printf("\n���� �Է�0");
		scanf("%c", &ch0);
		
		//while (getchar() != '\n');
		char ch;
		while(ch= cin.get() != '\n' &&
			   ch != EOF);

		printf("\n���� �Է�1");
		scanf("%c", &ch1);
		printf("\n���� �Է�");
		scanf("%d", &iValue);
		printf("\n�Ǽ� �Է�");
		scanf("%f", &fValue);
		printf("\n���ڿ� �Է�");
		scanf("%s", array);
		printf("\n%c %d %-10.2f",ch0, iValue, fValue);		
		printf("\n%s",array);
		printf("������ ����");
	}
#endif

