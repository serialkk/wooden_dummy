#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include "list.h"

#define PRINTALL  1   //1.모두 출력
#define FILESAVE  2	  //2.파일로 저장(to 파일)
#define FILELOAD  3	  //3.로드하기 (from 파일)
#define INPUTDATA 4	  //4.성적 입력
#define INPUTMAN  5	  //5.인원 추가
#define DELDATA   6	  //6.인원 삭제
#define SORTDATA  7	  //7.인원 정렬
#define FINDMAN   8	  //8.인원 검색
#define QUITPROG  9	  //9.프로그램 종료
#define ERASEALL  10  //10.데이터 삭제


void printMenu();            //  메뉴 출력
void printResult(Node* List);//1.전체 출력
void saveToFile(Node* List); //2.파일로 저장       
void loadToFile(Node** List);//3.파일로 부터 읽어옴
int inputData(Node* List);	 //4.성적 입력         
void inputMan(Node** List);	 //5.인원 추가         
int delData(Node* List);	 //6.인원 삭제  ★       
int sortData(Node* List);	 //7.인원 정렬  ★
Node* findMan(Node* List);	 //8.인원 검색  
Node* eraseAll(Node* List);	 //10.데이터 삭제


//student g_Student[3];
int g_iMenuNum;

int main(int argc, char* argv[]) 
{
	g_iMenuNum = 0;

	//리스트 구현부
	int   i = 0;
	int   Count = 0;
	Node* List = NULL;
	Node* Current = NULL;

	while (9 != g_iMenuNum) {

		switch (g_iMenuNum)
		{
		case PRINTALL:    //1.모두 출력
			printResult(List);
			break;		  
		case FILESAVE:	  //2.파일로 저장(to 파일)
			saveToFile(List);
			break;		  
		case FILELOAD:	  //3.로드하기 (from 파일)
			List = eraseAll(List);
			loadToFile(&List);
			break;		  
		case INPUTDATA:	  //4.성적 입력
			inputData(List);
			break;		  
		case INPUTMAN:	  //5.인원 추가
			inputMan(&List);
			break;		  
		case DELDATA:	  //6.인원 삭제
			delData(List);
			break;		  
		case SORTDATA:	  //7.인원 정렬
			sortData(List);
			getchar();
			getchar();
			break;		  
		case FINDMAN:	  //8.인원 검색
			Current = findMan(List);
			if (Current != NULL) {
				printf("=====================결과===================\n");
				printf("이름\t영어\t수학\t과학\t총점\t석차\t반\t번호\n");
				printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);
			}
			g_iMenuNum = 0;
			getchar();
			getchar();

			break;		  
		case QUITPROG:	  //9.프로그램 종료
			break;		  
		case ERASEALL:    //10.데이터 삭제
			List=eraseAll(List);
			printf("\n데이터 삭제가 완료 되었습니다\n");
			getchar();
			getchar();
			break;
		default:
			printMenu();
			break;
		}
	}

	printf("\n프로그램을 종료 합니다. 감사합니다.\n");
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

	printf("\n세이브가 완료 되었습니다\n");
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

	char name[8] = { 0 };   //이름
	int eng = 0;            //영어
	int math = 0;           //수학
	int sci = 0;            //과학
	int classroom = 0;      //반번호

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

	printf("\n로드가 완료 되었습니다\n");
	getchar();
	getchar();

	g_iMenuNum = 0;
}


void printMenu() {
	system("cls");
	printf("=====================메뉴===================\n");
	printf("1.모두 출력\n");
	printf("2.파일로 저장(to 파일)\n");
	printf("3.로드하기 (from 파일)\n");
	printf("4.인원 수정\n");
	printf("5.인원 추가\n");
	printf("6.인원 삭제\n");
	printf("7.인원 정렬\n");
	printf("8.인원 검색\n");
	printf("9.프로그램 종료\n");
	printf("10.데이터 삭제\n");
	printf("메뉴 번호 입력 하세요 > ");
	scanf("%d", &g_iMenuNum);
	fflush(stdin);
}
void printResult(Node* List) {
	/*  리스트 출력 */
	int   i = 0;
	int   Count = 0;
	Node* Current = NULL;

	if(List!=NULL)
		Count = getNodeCount(List);


	printf("=====================결과===================\n");
	printf("이름\t영어\t수학\t과학\t총점\t석차\t반\t번호\n");

	if(List == NULL)
		printf("\n데이터가 없습니다\n");

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

int inputData(Node* List) //4.성적 입력
{
	int i = 0, Count = 0;

	char name[10] = { 0 };   //이름
	int eng = 0;            //영어
	int math = 0;           //수학
	int sci = 0;            //과학
	int classroom = 0;      //반번호

	if (List == NULL) {
		printf("\n데이터가 없습니다\n");
		getchar();
		getchar();
		g_iMenuNum = 0;
		return 0;
	}

	Node* Current = NULL;
	
	Current=findMan(List);

	if (Current != NULL) {
		printf("=====================결과===================\n");
		printf("이름\t영어\t수학\t과학\t총점\t석차\t반\t번호\n");
		printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);

		printf("이름? > ");
		scanf("%s", name); strcpy(Current->Name, name);
		printf("\n영어? > ");
		scanf("%d", &eng); Current->eng = eng;
		printf("\n수학? > ");
		scanf("%d", &math); Current->math = math;
		printf("\n과학? > ");
		scanf("%d", &sci); Current->sci = sci;
		printf("\n반번호? > ");
		scanf("%d", &classroom); Current->classroom = classroom;

		printf("\n=================바뀐 결과===================\n");
		printf("이름\t영어\t수학\t과학\t총점\t석차\t반\t번호\n");
		printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);

	}
	g_iMenuNum = 0;
	getchar();
	getchar();
	return 0;
}
void inputMan(Node** List)	 //5.인원 추가
{
	Node* NewNode = NULL;
	Node temp;
	int i = 0;

	char name[10] = { 0 };   //이름
	int eng = 0;            //영어
	int math = 0;           //수학
	int sci = 0;            //과학
	int classroom = 0;      //반번호

	printf("이름? > ");
	scanf("%s", name);
	printf("\n영어? > ");
	scanf("%d", &eng);
	printf("\n수학? > ");
	scanf("%d", &math);
	printf("\n과학? > ");
	scanf("%d", &sci);
	printf("\n반번호? > ");
	scanf("%d", &classroom);
	
	temp.classroom = classroom; temp.eng = eng; temp.math = math; strcpy(temp.Name, name); temp.num = 0; temp.ranks = 0; temp.sci = sci; temp.total = sci+eng+math;


	NewNode = createNode(temp);
	appendNode(List, NewNode);


	g_iMenuNum = 0;
}
int delData(Node* List)	 //6.인원 삭제
{
	int i = 0, Count = 0;

	char name[10] = { 0 };   //이름
	int eng = 0;            //영어
	int math = 0;           //수학
	int sci = 0;            //과학
	int classroom = 0;      //반번호

	if (List == NULL) {
		printf("\n데이터가 없습니다.\n");
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

		printf("\n삭제 되었습니다.\n");
	}

	g_iMenuNum = 0;
	getchar();
	getchar();
	return 0;
}
int sortData(Node* List)	 //7.인원 정렬
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
		printf("\n데이터가 없습니다\n");
		g_iMenuNum = 0;
		return 0;
	}

	printf("\n총점으로 오름차순 정렬합니다.\n");
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

	printf("\n정렬 완료.\n");

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
Node* findMan(Node* List)	 //8.인원 검색
{
	int i = 0, Count = 0;

	char name[10] = { 0 };   //이름
	int eng = 0;            //영어
	int math = 0;           //수학
	int sci = 0;            //과학
	int classroom = 0;      //반번호

	Node* Current = NULL;


	if (List == NULL) {
		printf("\n데이터가 없습니다\n");
		return 0;
	}		
	printf("이름으로 검색 가능합니다. 이름을 입력해주세요 > ");
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
Node* eraseAll(Node* List)	 //10.데이터 삭제
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