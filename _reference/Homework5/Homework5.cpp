#include "Homework5.h"
///////////////////////////////////////////////////////////////////
// 1 ~ 37 ( ���� ) 2ĭ ����
// 1 ~ 19 ( ���� ) 1ĭ ����
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
			{  // ȭ�鿡 ��µɶ� �迭�� ��ġ�� ���߱����ؼ���  iCursorX => iCursorX/2 iCursorY=> iCursorY-1 �� �����
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
		printf("1p=��      2p=�� \n������ǥOmokBoard(%d %d)",iCursorX/2,iCursorY-1);  
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
					if(OmokBoard[j][i]==1) 			printf("��");
					else if(OmokBoard[j][i]==2)		printf("��");
					else if(OmokBoard[j][i]==0)		printf("��");
				}
				else if(j==18)
				{
					if(OmokBoard[j][i]==1)			printf("��");
					else if(OmokBoard[j][i]==2)		printf("��");
					else if(OmokBoard[j][i]==0)		printf("��");
				}
				else 
				{
					if(OmokBoard[j][i]==1)			printf("��");
					else if(OmokBoard[j][i]==2)		printf("��");
					else if(OmokBoard[j][i]==0)		printf("��");
				}
			}
			else if(i==18)
			{
				if(j==0) 
				{
					if(OmokBoard[j][i]==1)			printf("��");
					else if(OmokBoard[j][i]==2)		printf("��");
					else if(OmokBoard[j][i]==0)		printf("��");
				}
				else if(j==18) 
				{
					if(OmokBoard[j][i]==1)			printf("��");
					else if(OmokBoard[j][i]==2)		printf("��");
					else if(OmokBoard[j][i]==0)		printf("��");
				}
				else 
				{
					if(OmokBoard[j][i]==1)			printf("��");
					else if(OmokBoard[j][i]==2)		printf("��");
					else if(OmokBoard[j][i]==0)		printf("��");
				}
			}
			else
			{
				if(j==0) 
				{
					if(OmokBoard[j][i]==1)			printf("��");
					else if(OmokBoard[j][i]==2)		printf("��");
					else if(OmokBoard[j][i]==0)		printf("��");
				}				
				else if(j==18) 
				{
					if(OmokBoard[j][i]==1)			printf("��");
					else if(OmokBoard[j][i]==2)		printf("��");
					else if(OmokBoard[j][i]==0)		printf("��");
				}
				else
				{
					if(OmokBoard[j][i]==1)			printf("��");
					else if(OmokBoard[j][i]==2)		printf("��");
					else if(OmokBoard[j][i]==0)		printf("��");
				}
			}  
		} 
		printf("\n"); 
	}
	if (result == WHITEWIN) {
		printf("1p=�۰� �̰���ϴ�.");
	}
	else if (result == BLACKWIN) {
		printf("2p=�ܰ� �̰���ϴ�.");
	}
	else {
		GotoXY(2, 20);
		printf("����Ű�� ����Ű�� �̿��Ͽ� ���� �����ϴ�.");
		GotoXY(2, 21);  //������� ���� ����
		printf("1p=��      2p=�� \n������ǥOmokBoard(%d %d)", iCursorX / 2, iCursorY - 1);
		GotoXY(iCursorX, iCursorY);
	}
}
///////////////////////////////////////////////////////////////////
// return Value  0 ��������
//               1 ����������
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
			//1:�鵹,  2:�浹	
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
	// �����÷��̾� 
	bool bPlayer	= true;
	// ���� ���� ���� 
	int iGameLoop	= 1;

	// ������ �ʱ�ȭ ( �� / �� )
	for( int iRowBoard=0;iRowBoard<19;iRowBoard++)
	{
		for(int iColBoard=0;iColBoard<19;iColBoard++)
		{
			OmokBoard[iRowBoard][iColBoard]=0;
		}
	}

	// �������� �׸���.
	Drawboard(iGameLoop);

	// ���ӷ���
	while(iGameLoop!=WHITEWIN && iGameLoop!=BLACKWIN)
	{
		// Ű �Է�
		KeyCheck(bPlayer);
		// ��� ����
		iGameLoop=Judgment();
		// ���ŵ� �������� �׸���.
		Drawboard(iGameLoop);
		// ���� ��ü
		bPlayer = !bPlayer;		
	}
}
