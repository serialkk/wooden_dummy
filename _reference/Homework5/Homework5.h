//////////////////////  제어문/반복문 /////////////////////////
// 사용자 정의 함수사용
// while()
// switch() case:
// if ~ else
// for()
//////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>	//gotoxy(),SetConsoleCursorPosition()
#include <cstdio>
#include <cstdlib> 
#include <conio.h>		//kbhit(),getch()


#define	RIGHT	77
#define LEFT	75
#define UP		72
#define DOWN	80
#define ENTER	13

#define WHITEWIN 2
#define BLACKWIN 3

void	KeyCheck(bool bPlayer);
void	GotoXY(int x, int y);
void	Drawboard(int result);
int		Judgment();

int OmokBoard[19][19];               
int iCursorX=19;
int iCursorY=9;