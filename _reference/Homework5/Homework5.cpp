#include "Homework5.h"
///////////////////////////////////////////////////////////////////
// 1 ~ 37 ( 가로 ) 2칸 단위
// 1 ~ 19 ( 세로 ) 1칸 단위
///////////////////////////////////////////////////////////////////
void KeyCheck(bool bPlayer)
{	
	int iPlayTurn = 1;
	while(iPlayTurn)
	{
		switch(_getch())
		{
			case RIGHT:
			{
				iCursorX+=2;
				if(iCursorX>38) 
				{
					iCursorX-=2;
				}
				GotoXY(iCursorX,iCursorY);
				break;
			}
			case LEFT:
			{
				iCursorX-=2;
				if(iCursorX<0) 
				{
					iCursorX+=2;
				}
				GotoXY(iCursorX,iCursorY);
				break;
			}
			case UP:
			{
				iCursorY--;
				if(iCursorY<=0) 
				{
					iCursorY++;
				}
				GotoXY(iCursorX,iCursorY);
				break;
			}
			case DOWN:
			{
				iCursorY++;
				if(iCursorY>19) 
				{
					iCursorY--;
				}
				GotoXY(iCursorX,iCursorY);			  
				break;
			}
			case ENTER:
			{  // 화면에 출력될때 배열과 위치를 맞추기위해서는  iCursorX => iCursorX/2 iCursorY=> iCursorY-1 를 사용함
				if(OmokBoard[iCursorX/2][iCursorY-1]!=0) 
					break;   
	 
				if(!bPlayer)
				{
					OmokBoard[iCursorX/2][iCursorY-1]=2;
				}
				else
				{
					OmokBoard[iCursorX/2][iCursorY-1]=1;
				}			
				iPlayTurn=0;
			}  
		}
		GotoXY(2,21);
		printf("1p=○      2p=● \n현재좌표OmokBoard(%d %d)",iCursorX/2,iCursorY-1);  
		GotoXY(iCursorX,iCursorY); 
	}	
}
///////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////
void GotoXY(int x, int y)
{
	COORD Pos={x-1,y-1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}
///////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////
void Drawboard(int result)
{ 
	system("cls");
	int i,j;

	for( i=0;i<19;i++)
	{
		for(j=0;j<19;j++)
		{
			if(i==0)
			{
				if(j==0)
				{
					if(OmokBoard[j][i]==1) 			printf("○");
					else if(OmokBoard[j][i]==2)		printf("●");
					else if(OmokBoard[j][i]==0)		printf("┌");
				}
				else if(j==18)
				{
					if(OmokBoard[j][i]==1)			printf("○");
					else if(OmokBoard[j][i]==2)		printf("●");
					else if(OmokBoard[j][i]==0)		printf("┐");
				}
				else 
				{
					if(OmokBoard[j][i]==1)			printf("○");
					else if(OmokBoard[j][i]==2)		printf("●");
					else if(OmokBoard[j][i]==0)		printf("┬");
				}
			}
			else if(i==18)
			{
				if(j==0) 
				{
					if(OmokBoard[j][i]==1)			printf("○");
					else if(OmokBoard[j][i]==2)		printf("●");
					else if(OmokBoard[j][i]==0)		printf("└");
				}
				else if(j==18) 
				{
					if(OmokBoard[j][i]==1)			printf("○");
					else if(OmokBoard[j][i]==2)		printf("●");
					else if(OmokBoard[j][i]==0)		printf("┘");
				}
				else 
				{
					if(OmokBoard[j][i]==1)			printf("○");
					else if(OmokBoard[j][i]==2)		printf("●");
					else if(OmokBoard[j][i]==0)		printf("┴");
				}
			}
			else
			{
				if(j==0) 
				{
					if(OmokBoard[j][i]==1)			printf("○");
					else if(OmokBoard[j][i]==2)		printf("●");
					else if(OmokBoard[j][i]==0)		printf("├");
				}				
				else if(j==18) 
				{
					if(OmokBoard[j][i]==1)			printf("○");
					else if(OmokBoard[j][i]==2)		printf("●");
					else if(OmokBoard[j][i]==0)		printf("┤");
				}
				else
				{
					if(OmokBoard[j][i]==1)			printf("○");
					else if(OmokBoard[j][i]==2)		printf("●");
					else if(OmokBoard[j][i]==0)		printf("┼");
				}
			}  
		} 
		printf("\n"); 
	}
	if (result == WHITEWIN) {
		printf("1p=○가 이겼습니다.");
	}
	else if (result == BLACKWIN) {
		printf("2p=●가 이겼습니다.");
	}
	else {
		GotoXY(2, 20);
		printf("방향키와 엔터키를 이용하여 돌을 놓습니다.");
		GotoXY(2, 21);  //디버깅을 위해 수정
		printf("1p=○      2p=● \n현재좌표OmokBoard(%d %d)", iCursorX / 2, iCursorY - 1);
		GotoXY(iCursorX, iCursorY);
	}
}
///////////////////////////////////////////////////////////////////
// return Value  0 게임종료
//               1 게임진행중
///////////////////////////////////////////////////////////////////
int Judgment()
{
	int i = 0, j = 0, k = 0, l = 0, m=0,n=0;

	int cal[8][4] = { 0 };

	int total = 0;


	for (int iRowBoard = 0; iRowBoard<19; iRowBoard++)
	{
		for (int iColBoard = 0; iColBoard<19; iColBoard++)
		{
			//OmokBoard[iRowBoard][iColBoard] = 0;
			//1:백돌,  2:흑돌	
			for (l = 1; l < 3;l++){
				if (l == OmokBoard[iRowBoard][iColBoard]) {
					for (k = 1; k < 5;k++){

						if (l == OmokBoard[iRowBoard - (1 * k)][iColBoard - (1 * k)]) cal[0][0 + k - 1] = 1;
						if (l == OmokBoard[iRowBoard - (1 * k)][iColBoard + (0 * k)]) cal[1][0 + k - 1] = 1;
						if (l == OmokBoard[iRowBoard - (1 * k)][iColBoard + (1 * k)]) cal[2][0 + k - 1] = 1;
						if (l == OmokBoard[iRowBoard + (0 * k)][iColBoard + (1 * k)]) cal[3][0 + k - 1] = 1;
						if (l == OmokBoard[iRowBoard + (1 * k)][iColBoard + (1 * k)]) cal[4][0 + k - 1] = 1;
						if (l == OmokBoard[iRowBoard + (1 * k)][iColBoard + (0 * k)]) cal[5][0 + k - 1] = 1;
						if (l == OmokBoard[iRowBoard + (1 * k)][iColBoard - (1 * k)]) cal[6][0 + k - 1] = 1;
						if (l == OmokBoard[iRowBoard + (0 * k)][iColBoard - (1 * k)]) cal[7][0 + k - 1] = 1;

					}
				
					for (i = 0; i < 8; i++) {
						for (j = 0; j < 4; j++) {
							total += cal[i][j];
						}

						if (total == 4) {
							if (1 == l)
								return WHITEWIN;
							else if (2 == l)
								return BLACKWIN;
						}
						else {
							total = 0;
						}
					}

					for (i = 0; i < 8; i++) {
						for (j = 0; j < 4; j++) {
							cal[i][j] = 0;
						}

					}
				}
			}
		}
	}

  return 1;
}
///////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////
void main()
{
	// 게임플레이어 
	bool bPlayer	= true;
	// 게임 진행 판정 
	int iGameLoop	= 1;

	// 오목판 초기화 ( 행 / 열 )
	for( int iRowBoard=0;iRowBoard<19;iRowBoard++)
	{
		for(int iColBoard=0;iColBoard<19;iColBoard++)
		{
			OmokBoard[iRowBoard][iColBoard]=0;
		}
	}

	// 오목판을 그린다.
	Drawboard(iGameLoop);

	// 게임루프
	while(iGameLoop!=WHITEWIN && iGameLoop!=BLACKWIN)
	{
		// 키 입력
		KeyCheck(bPlayer);
		// 결과 판정
		iGameLoop=Judgment();
		// 갱신된 오목판을 그린다.
		Drawboard(iGameLoop);
		// 선수 교체
		bPlayer = !bPlayer;		
	}
}
