#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include "list.h"

#define PRINTALL  1   //1.��� ���
#define FILESAVE  2	  //2.���Ϸ� ����(to ����)
#define FILELOAD  3	  //3.�ε��ϱ� (from ����)
#define INPUTDATA 4	  //4.���� �Է�
#define INPUTMAN  5	  //5.�ο� �߰�
#define DELDATA   6	  //6.�ο� ����
#define SORTDATA  7	  //7.�ο� ����
#define FINDMAN   8	  //8.�ο� �˻�
#define QUITPROG  9	  //9.���α׷� ����
#define ERASEALL  10  //10.������ ����


void printMenu();            //  �޴� ���
void printResult(Node* List);//1.��ü ���
void saveToFile(Node* List); //2.���Ϸ� ����       
void loadToFile(Node** List);//3.���Ϸ� ���� �о��
int inputData(Node* List);	 //4.���� �Է�         
void inputMan(Node** List);	 //5.�ο� �߰�         
int delData(Node* List);	 //6.�ο� ����  ��       
int sortData(Node* List);	 //7.�ο� ����  ��
Node* findMan(Node* List);	 //8.�ο� �˻�  
Node* eraseAll(Node* List);	 //10.������ ����


//student g_Student[3];
int g_iMenuNum;

int main(int argc, char* argv[]) 
{
	g_iMenuNum = 0;

	//����Ʈ ������
	int   i = 0;
	int   Count = 0;
	Node* List = NULL;
	Node* Current = NULL;

	while (9 != g_iMenuNum) {

		switch (g_iMenuNum)
		{
		case PRINTALL:    //1.��� ���
			printResult(List);
			break;		  
		case FILESAVE:	  //2.���Ϸ� ����(to ����)
			saveToFile(List);
			break;		  
		case FILELOAD:	  //3.�ε��ϱ� (from ����)
			List = eraseAll(List);
			loadToFile(&List);
			break;		  
		case INPUTDATA:	  //4.���� �Է�
			inputData(List);
			break;		  
		case INPUTMAN:	  //5.�ο� �߰�
			inputMan(&List);
			break;		  
		case DELDATA:	  //6.�ο� ����
			delData(List);
			break;		  
		case SORTDATA:	  //7.�ο� ����
			sortData(List);
			getchar();
			getchar();
			break;		  
		case FINDMAN:	  //8.�ο� �˻�
			Current = findMan(List);
			if (Current != NULL) {
				printf("=====================���===================\n");
				printf("�̸�\t����\t����\t����\t����\t����\t��\t��ȣ\n");
				printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);
			}
			g_iMenuNum = 0;
			getchar();
			getchar();

			break;		  
		case QUITPROG:	  //9.���α׷� ����
			break;		  
		case ERASEALL:    //10.������ ����
			List=eraseAll(List);
			printf("\n������ ������ �Ϸ� �Ǿ����ϴ�\n");
			getchar();
			getchar();
			break;
		default:
			printMenu();
			break;
		}
	}

	printf("\n���α׷��� ���� �մϴ�. �����մϴ�.\n");
	return 0;
}

void saveToFile(Node* List) {

	int   i = 0, Count = 0;
	Node* Current = NULL;
	char buffer[256] = { 0 };
	char buffer2[256] = { 0 };
	FILE *f;

	Count = getNodeCount(List);

	f = fopen("StudentData.dat", "wt");

	
	fprintf(f, buffer);
	
	for (i = 0; i<Count; i++)
	{
		Current = getNodeAt(List, i);
		
		if(i!=0)
			strcat(buffer, "\n");

		strcat(buffer, Current->Name); strcat(buffer, "\t");
		_itoa(Current->eng, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * 256);
		_itoa(Current->math, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * 256);
		_itoa(Current->sci, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * 256);
		_itoa(Current->total, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * 256);
		_itoa(Current->ranks, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * 256);
		_itoa(Current->classroom, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * 256);
		_itoa(Current->num, buffer2, 10); strcat(buffer, buffer2);  memset(buffer2, 0, sizeof(char) * 256);
		fprintf(f, buffer);
		memset(buffer, 0, sizeof(char) * 256);
	}
	//fprintf(f, "%c", 26);//EOF
	fclose(f);

	printf("\n���̺갡 �Ϸ� �Ǿ����ϴ�\n");
	getchar();
	getchar();

	g_iMenuNum = 0;
}
void loadToFile(Node** List) {

	FILE    *fp_src;

	Node temp;
	Node* NewNode = NULL;
	char pBuffer[256];
	int iCount = 0, Count = 0;

	char name[8] = { 0 };   //�̸�
	int eng = 0;            //����
	int math = 0;           //����
	int sci = 0;            //����
	int classroom = 0;      //�ݹ�ȣ

	temp.classroom = classroom;temp.eng = eng;temp.math = math;strcpy(temp.Name, name);temp.num = 0;temp.ranks = 0;temp.sci = sci;temp.total = sci + eng + math;

	fp_src = fopen("StudentData.dat", "rt");
	

	while (!feof(fp_src))
	{
		fgets(pBuffer, 256, fp_src);
		sscanf(pBuffer, "%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d", temp.Name, &temp.eng, &temp.math, &temp.sci, &temp.total, &temp.ranks, &temp.classroom, &temp.num);

		NewNode = createNode(temp);
		appendNode(List, NewNode);
		
	}

	fclose(fp_src);

	printf("\n�ε尡 �Ϸ� �Ǿ����ϴ�\n");
	getchar();
	getchar();

	g_iMenuNum = 0;
}


void printMenu() {
	system("cls");
	printf("=====================�޴�===================\n");
	printf("1.��� ���\n");
	printf("2.���Ϸ� ����(to ����)\n");
	printf("3.�ε��ϱ� (from ����)\n");
	printf("4.�ο� ����\n");
	printf("5.�ο� �߰�\n");
	printf("6.�ο� ����\n");
	printf("7.�ο� ����\n");
	printf("8.�ο� �˻�\n");
	printf("9.���α׷� ����\n");
	printf("10.������ ����\n");
	printf("�޴� ��ȣ �Է� �ϼ��� > ");
	scanf("%d", &g_iMenuNum);
	fflush(stdin);
}
void printResult(Node* List) {
	/*  ����Ʈ ��� */
	int   i = 0;
	int   Count = 0;
	Node* Current = NULL;

	if(List!=NULL)
		Count = getNodeCount(List);


	printf("=====================���===================\n");
	printf("�̸�\t����\t����\t����\t����\t����\t��\t��ȣ\n");

	if(List == NULL)
		printf("\n�����Ͱ� �����ϴ�\n");

	for (i = 0; i<Count; i++)
	{
		Current = getNodeAt(List, i);

		if (Current != NULL)
			printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);
		
	}
	getchar();
	getchar();
	g_iMenuNum = 0;
}

int inputData(Node* List) //4.���� �Է�
{
	int i = 0, Count = 0;

	char name[10] = { 0 };   //�̸�
	int eng = 0;            //����
	int math = 0;           //����
	int sci = 0;            //����
	int classroom = 0;      //�ݹ�ȣ

	if (List == NULL) {
		printf("\n�����Ͱ� �����ϴ�\n");
		getchar();
		getchar();
		g_iMenuNum = 0;
		return 0;
	}

	Node* Current = NULL;
	
	Current=findMan(List);

	if (Current != NULL) {
		printf("=====================���===================\n");
		printf("�̸�\t����\t����\t����\t����\t����\t��\t��ȣ\n");
		printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);

		printf("�̸�? > ");
		scanf("%s", name); strcpy(Current->Name, name);
		printf("\n����? > ");
		scanf("%d", &eng); Current->eng = eng;
		printf("\n����? > ");
		scanf("%d", &math); Current->math = math;
		printf("\n����? > ");
		scanf("%d", &sci); Current->sci = sci;
		printf("\n�ݹ�ȣ? > ");
		scanf("%d", &classroom); Current->classroom = classroom;

		printf("\n=================�ٲ� ���===================\n");
		printf("�̸�\t����\t����\t����\t����\t����\t��\t��ȣ\n");
		printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);

	}
	g_iMenuNum = 0;
	getchar();
	getchar();
	return 0;
}
void inputMan(Node** List)	 //5.�ο� �߰�
{
	Node* NewNode = NULL;
	Node temp;
	int i = 0;

	char name[10] = { 0 };   //�̸�
	int eng = 0;            //����
	int math = 0;           //����
	int sci = 0;            //����
	int classroom = 0;      //�ݹ�ȣ

	printf("�̸�? > ");
	scanf("%s", name);
	printf("\n����? > ");
	scanf("%d", &eng);
	printf("\n����? > ");
	scanf("%d", &math);
	printf("\n����? > ");
	scanf("%d", &sci);
	printf("\n�ݹ�ȣ? > ");
	scanf("%d", &classroom);
	
	temp.classroom = classroom; temp.eng = eng; temp.math = math; strcpy(temp.Name, name); temp.num = 0; temp.ranks = 0; temp.sci = sci; temp.total = sci+eng+math;


	NewNode = createNode(temp);
	appendNode(List, NewNode);


	g_iMenuNum = 0;
}
int delData(Node* List)	 //6.�ο� ����
{
	int i = 0, Count = 0;

	char name[10] = { 0 };   //�̸�
	int eng = 0;            //����
	int math = 0;           //����
	int sci = 0;            //����
	int classroom = 0;      //�ݹ�ȣ

	if (List == NULL) {
		printf("\n�����Ͱ� �����ϴ�.\n");
		getchar();
		getchar();
		g_iMenuNum = 0;
		return 0;
	}

	Node* Current = NULL;

	Current = findMan(List);

	if (Current != NULL)
	{
		removeNode(&List, Current);
		destroyNode(Current);

		printf("\n���� �Ǿ����ϴ�.\n");
	}

	g_iMenuNum = 0;
	getchar();
	getchar();
	return 0;
}
int sortData(Node* List)	 //7.�ο� ����
{
	int i = 0,j=0, Count = 0;
	Node* temp;
	Node* Current = NULL;
	Node hold;
	Node temp_for_append;
	Node* NewNode = NULL;


	if (List != NULL)
		Count = getNodeCount(List);

	temp = (Node*)malloc(sizeof(Node)*Count);

	
	if (List == NULL) {
		printf("\n�����Ͱ� �����ϴ�\n");
		g_iMenuNum = 0;
		return 0;
	}

	printf("\n�������� �������� �����մϴ�.\n");
	for (i = 0; i<Count; i++)
	{
		Current = getNodeAt(List, i);

		if (Current != NULL)
			memcpy(&temp[i], Current, sizeof(Node));

	}
	
	//Bubble Sort
	for (i = 0; i < Count - 1; i++) {
		for (j = 0; j < Count - 1 - i; j++) {
			if (temp[j].total > temp[j + 1].total) {

				memcpy(&hold,&temp[j],sizeof(Node));

				memcpy(&temp[j],&temp[j + 1], sizeof(Node));

				memcpy(&temp[j + 1],&hold, sizeof(Node));
			}
		}
	}

	printf("\n���� �Ϸ�.\n");

	List = eraseAll(List);

	for (i = 0; i < Count; i++) {
		memset(&temp_for_append, 0, sizeof(Node));
		memcpy(&temp_for_append, &temp[i], sizeof(Node));
		NewNode = createNode(temp_for_append);
		appendNode(&List, NewNode);
	}

	g_iMenuNum = 0;


	free(temp);
}
Node* findMan(Node* List)	 //8.�ο� �˻�
{
	int i = 0, Count = 0;

	char name[10] = { 0 };   //�̸�
	int eng = 0;            //����
	int math = 0;           //����
	int sci = 0;            //����
	int classroom = 0;      //�ݹ�ȣ

	Node* Current = NULL;


	if (List == NULL) {
		printf("\n�����Ͱ� �����ϴ�\n");
		return 0;
	}		
	printf("�̸����� �˻� �����մϴ�. �̸��� �Է����ּ��� > ");
	scanf("%s", name);


	
	if (List != NULL)
		Count = getNodeCount(List);



	for (i = 0; i<Count; i++)
	{
		Current = getNodeAt(List, i);

		if (strcmp(Current->Name, name) == 0)
			//printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);

			return Current;
	}
	return 0;
}
Node* eraseAll(Node* List)	 //10.������ ����
{
	int   i = 0;
	int   Count = 0;
	Node* Current = NULL;

	Count = getNodeCount(List);

	for (i = 0; i<Count; i++)
	{
		Current = getNodeAt(List, 0);

		if (Current != NULL)
		{
			removeNode(&List, Current);
			destroyNode(Current);
		}
	}

	g_iMenuNum = 0;
	return NULL;
}