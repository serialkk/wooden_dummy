#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include "StudentManagement.h"


CStudentManagement::menu_item CStudentManagement::g_iMenuNum = FIRSTSCREEN;

int main(int argc, char* argv[]) 
{

	//CStudentManagement 객체생성
	CStudentManagement StudentMangement;

	//CStudentManagement 실행 함수 호출
	StudentMangement.run();

	//StudentMangement.run2();

	printf("\n프로그램을 종료 합니다. 감사합니다.\n");
	return 0;
}

void CStudentManagement::saveToFile(CStudent* List) const {

	int   i = 0, Count = 0;
	CStudent* Current = NULL;
	char buffer[256] = { 0 };
	
	FILE *f;

	Count = m_sll_list.countNodes(List);

	f = fopen("StudentData.dat", "wt");

	
	fprintf(f, buffer);
	
	for (i = 0; i<Count; i++)
	{
		Current = m_sll_list.findNode(List, i);
		
		if(i!=0)
			strcat(buffer, "\n");

		///
		Current->print_to_buffer(buffer, 256);

		fprintf(f, buffer);
		memset(buffer, 0, sizeof(char) * 256);
	}

	fclose(f);

	printf("\n세이브가 완료 되었습니다\n");
	getchar();
	getchar();

	g_iMenuNum = FIRSTSCREEN;
}
void CStudentManagement::loadToFile(CStudent** List) {

	FILE    *fp_src;

	CStudent temp;
	CStudent* NewNode = NULL;
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

		NewNode = m_sll_list.createNode(temp);
		m_sll_list.appendNode(List, NewNode);
		
	}

	fclose(fp_src);

	printf("\n로드가 완료 되었습니다\n");
	getchar();
	getchar();

	g_iMenuNum = FIRSTSCREEN;
}


void CStudentManagement::printMenu() const {
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
void CStudentManagement::printResult(CStudent* List) const {
	/*  리스트 출력 */
	int   i = 0;
	int   Count = 0;
	CStudent* Current = NULL;

	if(List!=NULL)
		Count = m_sll_list.countNodes(List);


	printf("=====================결과===================\n");
	printf("이름\t영어\t수학\t과학\t총점\t석차\t반\t번호\n");

	if(List == NULL)
		printf("\n데이터가 없습니다\n");

	for (i = 0; i<Count; i++)
	{
		Current = m_sll_list.findNode(List, i);

		if (Current != NULL)
			cout<<*Current<<endl;
			//printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);
		
	}
	getchar();
	getchar();
	g_iMenuNum = FIRSTSCREEN;
}

int CStudentManagement::inputData(CStudent* List) //4.성적 입력
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
		g_iMenuNum = FIRSTSCREEN;
		return 0;
	}

	CStudent* Current = NULL;
	
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
	g_iMenuNum = FIRSTSCREEN;
	getchar();
	getchar();
	return 0;
}
void CStudentManagement::inputMan(CStudent** List)	 //5.인원 추가
{
	CStudent* NewNode = NULL;
	CStudent temp;
	int i = 0;

	char name[10] = { 0 };   //이름
	int eng = 0;            //영어
	int math = 0;           //수학
	int sci = 0;            //과학
	int classroom = 0;      //반번호

	std::cin >> temp;


	NewNode = m_sll_list.createNode(temp);
	m_sll_list.appendNode(List, NewNode);


	g_iMenuNum = FIRSTSCREEN;
}

void CStudentManagement::inputRandomMan(CStudent** List)	 //5.인원 추가
{
	CStudent* NewNode = NULL;
	CStudent temp;
	int i = 0;



	for (i = 0; i < 5; i++) {
		char cWord = 65 + rand() % 26;
		temp.Name[i] = cWord;
	}
	temp.Name[5] = 0;

	temp.eng = rand() % 101;
	temp.math = rand() % 101;
	temp.sci = rand() % 101;
	temp.num = rand() % 101;
	temp.ranks = rand() % 101;
	temp.classroom = rand() % 10;
	temp.total = temp.eng + temp.math + temp.sci;


	//std::cin >> temp;


	NewNode = m_sll_list.createNode(temp);
	m_sll_list.appendNode(List, NewNode);


	g_iMenuNum = FIRSTSCREEN;
}

int CStudentManagement::delData(CStudent* List)	 //6.인원 삭제
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
		g_iMenuNum = FIRSTSCREEN;
		return 0;
	}

	CStudent* Current = NULL;

	Current = findMan(List);

	if (Current != NULL)
	{
		m_sll_list.removeNode(&List, Current);
		m_sll_list.destroyNode(Current);

		printf("\n삭제 되었습니다.\n");
	}

	g_iMenuNum = FIRSTSCREEN;
	getchar();
	getchar();
	return 0;
}
int CStudentManagement::sortData(CStudent** List, bool isUp)	 //7.인원 정렬
{
	int i = 0,j=0, Count = 0;
	int input = 0;
	CStudent* temp;
	CStudent* Current = NULL;
	CStudent hold;
	CStudent temp_for_append;
	CStudent* NewNode = NULL;


	if (List != NULL)
		Count = m_sll_list.countNodes(*List);

	temp = (CStudent*)malloc(sizeof(CStudent)*Count);

	
	if (List == NULL) {
		printf("\n데이터가 없습니다\n");
		g_iMenuNum = FIRSTSCREEN;
		return 0;
	}

	//input = up;
	printf("\n 1:내림차순 2:오름차순 입력. default:내림차순>");
	scanf("%d", &input);


	if (input == 2)
		printf("\n총점으로 오름차순 정렬합니다.\n");
	else
		printf("\n총점으로 내림차순 정렬합니다.\n");

	for (i = 0; i<Count; i++)
	{
		Current = m_sll_list.findNode(*List, i);

		if (Current != NULL)
			memcpy(&temp[i], Current, sizeof(CStudent));

	}

	//Bubble Sort
	for (i = 0; i < Count - 1; i++) {
		for (j = 0; j < Count - 1 - i; j++) {

			if (input == 2) {
				if (temp[j].total > temp[j + 1].total) {

					memcpy(&hold, &temp[j], sizeof(CStudent));

					memcpy(&temp[j], &temp[j + 1], sizeof(CStudent));

					memcpy(&temp[j + 1], &hold, sizeof(CStudent));
				}
			}
			else {
				if (temp[j].total < temp[j + 1].total) {

					memcpy(&hold, &temp[j], sizeof(CStudent));

					memcpy(&temp[j], &temp[j + 1], sizeof(CStudent));

					memcpy(&temp[j + 1], &hold, sizeof(CStudent));
				}
			}
		}
	}

	printf("\n정렬 완료.\n");

	*List = eraseAll(*List);

	for (i = 0; i < Count; i++) {
		memset(&temp_for_append, 0, sizeof(CStudent));
		memcpy(&temp_for_append, &temp[i], sizeof(CStudent));
		NewNode = m_sll_list.createNode(temp_for_append);
		m_sll_list.appendNode(List, NewNode);
	}

	g_iMenuNum = FIRSTSCREEN;


	free(temp);

	return 0;
}
CStudent* CStudentManagement::findMan(CStudent* List) const	 //8.인원 검색
{
	int i = 0, Count = 0;

	char name[10] = { 0 };   //이름
	int eng = 0;            //영어
	int math = 0;           //수학
	int sci = 0;            //과학
	int classroom = 0;      //반번호

	CStudent* Current = NULL;


	if (List == NULL) {
		printf("\n데이터가 없습니다\n");
		return 0;
	}		
	printf("이름으로 검색 가능합니다. 이름을 입력해주세요 > ");
	scanf("%s", name);
	
	if (List != NULL)
		Count = m_sll_list.countNodes(List);

	for (i = 0; i<Count; i++)
	{
		Current = m_sll_list.findNode(List, i);

		if (strcmp(Current->Name, name) == 0)
			return Current;
	}
	return 0;
}
CStudent* CStudentManagement::eraseAll(CStudent* List)	 //10.데이터 삭제
{
	int   i = 0;
	int   Count = 0;
	CStudent* Current = NULL;

	Count = m_sll_list.countNodes(List);

	for (i = 0; i<Count; i++)
	{
		Current = m_sll_list.findNode(List, 0);

		if (Current != NULL)
		{
			m_sll_list.removeNode(&List, Current);
			m_sll_list.destroyNode(Current);
		}
	}

	g_iMenuNum = FIRSTSCREEN;
	return NULL;
}

void CStudentManagement::run() {

	for (int i = 0; i < 10; i++)
	{
		inputRandomMan(&m_List);
	}
	
	while (9 != g_iMenuNum) {

		switch (g_iMenuNum)
		{
		case PRINTALL:    //1.모두 출력
			printResult(m_List);
			break;
		case FILESAVE:	  //2.파일로 저장(to 파일)
			saveToFile(m_List);
			break;
		case FILELOAD:	  //3.로드하기 (from 파일)
			m_List = eraseAll(m_List);
			loadToFile( &m_List);
			break;
		case INPUTDATA:	  //4.성적 입력
			inputData(m_List);
			break;
		case INPUTMAN:	  //5.인원 추가
			inputMan(&m_List);
			break;
		case DELDATA:	  //6.인원 삭제
			delData(m_List);
			break;
		case SORTDATA:	  //7.인원 정렬
			sortData(&m_List);
			getchar();
			getchar();
			break;
		case FINDMAN:	  //8.인원 검색
			m_Current = (CStudent*)findMan(m_List);
			if (m_Current != NULL) {
				printf("=====================결과===================\n");
				printf("이름\t영어\t수학\t과학\t총점\t석차\t반\t번호\n");
				printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", m_Current->Name, m_Current->eng, m_Current->math, m_Current->sci, m_Current->total, m_Current->ranks, m_Current->classroom, m_Current->num);
			}
			g_iMenuNum = FIRSTSCREEN;
			getchar();
			getchar();

			break;
		case QUITPROG:	  //9.프로그램 종료
			break;
		case ERASEALL:    //10.데이터 삭제
			m_List = eraseAll(m_List);
			printf("\n데이터 삭제가 완료 되었습니다\n");
			getchar();
			getchar();
			break;
		default:
			printMenu();
			break;
		}
	}
}

void CStudentManagement::run2() {

	while (9 != g_iMenuNum) {

		switch (g_iMenuNum)
		{
		case PRINTALL:    //1.모두 출력
			printResult(*m_List);
			break;
		case FILESAVE:	  //2.파일로 저장(to 파일)
			saveToFile(*m_List);
			break;
		case FILELOAD:	  //3.로드하기 (from 파일)
			m_List = eraseAll(m_List);
			loadToFile(&m_List);
			break;
		case INPUTDATA:	  //4.성적 입력
			inputData(*m_List);
			break;
		case INPUTMAN:	  //5.인원 추가
			inputMan(&m_List);
			break;
		case DELDATA:	  //6.인원 삭제
			delData(m_List);
			break;
		case SORTDATA:	  //7.인원 정렬
			sortData(&m_List);
			getchar();
			getchar();
			break;
		case FINDMAN:	  //8.인원 검색
			m_Current = findMan(m_List);
			if (m_Current != NULL) {
				printf("=====================결과===================\n");
				printf("이름\t영어\t수학\t과학\t총점\t석차\t반\t번호\n");
				printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", m_Current->Name, m_Current->eng, m_Current->math, m_Current->sci, m_Current->total, m_Current->ranks, m_Current->classroom, m_Current->num);
			}
			g_iMenuNum = FIRSTSCREEN;
			getchar();
			getchar();

			break;
		case QUITPROG:	  //9.프로그램 종료
			break;
		case ERASEALL:    //10.데이터 삭제
			m_List = eraseAll(m_List);
			printf("\n데이터 삭제가 완료 되었습니다\n");
			getchar();
			getchar();
			break;
		default:
			printMenu();
			break;
		}
	}
}

CStudentManagement::CStudentManagement() {
	 m_List = NULL;
	 m_Current = NULL;
}
CStudentManagement::~CStudentManagement() {

}


void CStudentManagement::printResult(CStudent& List) const {
	/*  리스트 출력 */
	int   i = 0;
	int   Count = 0;
	CStudent* Current = NULL;

	//if (List != NULL)
		Count = m_sll_list.countNodes(&List);


	printf("=====================결과===================\n");
	printf("이름\t영어\t수학\t과학\t총점\t석차\t반\t번호\n");

	//if (List == NULL)
	//	printf("\n데이터가 없습니다\n");

	for (i = 0; i<Count; i++)
	{
		Current = (CStudent*)m_sll_list.findNode(&List, i);

		if (Current != NULL)
			printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);

	}
	getchar();
	getchar();
	g_iMenuNum = FIRSTSCREEN;

} //1.전체 출력

void CStudentManagement::saveToFile(CStudent& List) const {
	int   i = 0, Count = 0;
	CStudent* Current = NULL;
	char buffer[256] = { 0 };
	char buffer2[256] = { 0 };
	FILE *f;

	Count = m_sll_list.countNodes(&List);

	f = fopen("StudentData.dat", "wt");


	fprintf(f, buffer);

	for (i = 0; i<Count; i++)
	{
		Current = m_sll_list.findNode(&List, i);

		if (i != 0)
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

	fclose(f);

	printf("\n세이브가 완료 되었습니다\n");
	getchar();
	getchar();

	g_iMenuNum = FIRSTSCREEN;

}  //2.파일로 저장 

//void CStudentManagement::loadToFile(Node** List) {}//3.파일로 부터 읽어옴

int CStudentManagement::inputData(CStudent& List) {

	int i = 0, Count = 0;

	char name[10] = { 0 };   //이름
	int eng = 0;            //영어
	int math = 0;           //수학
	int sci = 0;            //과학
	int classroom = 0;      //반번호

	/*
	if (List == NULL) {
		printf("\n데이터가 없습니다\n");
		getchar();
		getchar();
		g_iMenuNum = FIRSTSCREEN;
		return 0;
	}
	*/

	CStudent* Current = NULL;

	Current = (CStudent*)findMan(&List);

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
	g_iMenuNum = FIRSTSCREEN;
	getchar();
	getchar();

	return 0;
} 	
