#include <stdio.h>
void Fun1()
{
	int iValue = 999;
	printf("\n%s iValue = %d",
		"KGCA GAME ACADEMY!", iValue);
}
void Fun()
{
	int iValue[] = {0,1,2,3};
	printf("\n%s iValue = %d",
		"KGCA GAME ACADEMY!", iValue);
	Fun1();
}
void main()
{
	Fun();
	getchar();
}
