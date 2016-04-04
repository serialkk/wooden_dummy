#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include "StudentManagement.h"


CStudentManagement::menu_item CStudentManagement::g_iMenuNum = FIRSTSCREEN;

int main(int argc, char* argv[]) 
{

	//CStudentManagement ��ü����
	CStudentManagement StudentMangement;

	//CStudentManagement ���� �Լ� ȣ��
	StudentMangement.run();

	//StudentMangement.run2();

	printf("\n���α׷��� ���� �մϴ�. �����մϴ�.\n");
	return 0;
}

void CStudentManagement::saveToFile(CStudent* List) const {

	int   i = 0, Count = 0;
	CStudent* Current = NULL;
	char buffer[256] = { 0 };
	
	FILE *f;

	Count = m_list_manage.countNodes(List);

	f = fopen("StudentData.dat", "wt");

	
	fprintf(f, buffer);
	
	for (i = 0; i<Count; i++)
	{
		Current = m_list_manage.findNode(List, i);
		
		if(i!=0)
			strcat(buffer, "\n");

		///
		Current->print_to_buffer(buffer, 256);

		fprintf(f, buffer);
		memset(buffer, 0, sizeof(char) * 256);
	}

	fclose(f);

	printf("\n���̺갡 �Ϸ� �Ǿ����ϴ�\n");
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

		NewNode = m_list_manage.createNode(temp);
		m_list_manage.appendNode(List, NewNode);
		
	}

	fclose(fp_src);

	printf("\n�ε尡 �Ϸ� �Ǿ����ϴ�\n");
	getchar();
	getchar();

	g_iMenuNum = FIRSTSCREEN;
}


void CStudentManagement::printMenu() const {
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
void CStudentManagement::printResult(CStudent* List) const {
	/*  ����Ʈ ��� */
	int   i = 0;
	int   Count = 0;
	CStudent* Current = NULL;

	if(List!=NULL)
		Count = m_list_manage.countNodes(List);


	printf("=====================���===================\n");
	printf("�̸�\t����\t����\t����\t����\t����\t��\t��ȣ\n");

	if(List == NULL)
		printf("\n�����Ͱ� �����ϴ�\n");

	for (i = 0; i<Count; i++)
	{
		Current = m_list_manage.findNode(List, i);

		if (Current != NULL)
			cout<<*Current<<endl;
			//printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);
		
	}
	getchar();
	getchar();
	g_iMenuNum = FIRSTSCREEN;
}

int CStudentManagement::inputData(CStudent* List) //4.���� �Է�
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
		g_iMenuNum = FIRSTSCREEN;
		return 0;
	}

	CStudent* Current = NULL;
	
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
	g_iMenuNum = FIRSTSCREEN;
	getchar();
	getchar();
	return 0;
}
void CStudentManagement::inputMan(CStudent** List)	 //5.�ο� �߰�
{
	CStudent* NewNode = NULL;
	CStudent temp;
	int i = 0;

	char name[10] = { 0 };   //�̸�
	int eng = 0;            //����
	int math = 0;           //����
	int sci = 0;            //����
	int classroom = 0;      //�ݹ�ȣ

	std::cin >> temp;


	NewNode = m_list_manage.createNode(temp);
	m_list_manage.appendNode(List, NewNode);


	g_iMenuNum = FIRSTSCREEN;
}

void CStudentManagement::inputRandomMan(CStudent** List)	 //5.�ο� �߰�
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


	NewNode = m_list_manage.createNode(temp);
	m_list_manage.appendNode(List, NewNode);


	g_iMenuNum = FIRSTSCREEN;
}

int CStudentManagement::delData(CStudent* List)	 //6.�ο� ����
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
		g_iMenuNum = FIRSTSCREEN;
		return 0;
	}

	CStudent* Current = NULL;

	Current = findMan(List);

	if (Current != NULL)
	{
		m_list_manage.removeNode(&List, Current);
		m_list_manage.destroyNode(Current);

		printf("\n���� �Ǿ����ϴ�.\n");
	}

	g_iMenuNum = FIRSTSCREEN;
	getchar();
	getchar();
	return 0;
}
int CStudentManagement::sortData(CStudent** List, bool isUp)	 //7.�ο� ����
{
	int i = 0,j=0, indexMin = 0, Count = 0;
	int input = 0;
	CStudent* temp1,*temp2;
	CStudent* Current = NULL;
	CStudent hold;
	CStudent temp_for_append;
	CStudent* NewNode = NULL;

	if (List != NULL)
		Count = m_list_manage.countNodes(*List);

	//temp = (CStudent*)malloc(sizeof(CStudent)*Count);

	
	if (List == NULL) {
		printf("\n�����Ͱ� �����ϴ�\n");
		g_iMenuNum = FIRSTSCREEN;
		return 0;
	}

	//input = up;
	printf("\n 1:�������� 2:�������� �Է�. default:��������>");
	scanf("%d", &input);


	if (input == 2)
		printf("\n�������� �������� �����մϴ�.\n");
	else
		printf("\n�������� �������� �����մϴ�.\n");
	
	//m_sll_list.findNode(*List, j);

	for (i = 0; i < Count -1 ; i++)
	{
		indexMin = i;
		for (j = i + 1; j < Count ; j++)
		{

			if (input == 2) {
				//��������
				if (m_list_manage.findNode(*List, j)->total < m_list_manage.findNode(*List, indexMin)->total)
					indexMin = j;
			}
			else {
				//��������
				if (m_list_manage.findNode(*List, j)->total > m_list_manage.findNode(*List, indexMin)->total)
					indexMin = j;
			}

		}

		/*
		temp = list[indexMin];
		list[indexMin] = list[i];
		list[i] = temp;
		*/
		temp1 = m_list_manage.findNode(*List, i);
		temp2 = m_list_manage.findNode(*List, indexMin);

		m_list_manage.swap(&temp1, &temp2);
	}


	g_iMenuNum = FIRSTSCREEN;


	//free(temp);

	return 0;
}
CStudent* CStudentManagement::findMan(CStudent* List) const	 //8.�ο� �˻�
{
	int i = 0, Count = 0;

	char name[10] = { 0 };   //�̸�
	int eng = 0;            //����
	int math = 0;           //����
	int sci = 0;            //����
	int classroom = 0;      //�ݹ�ȣ

	CStudent* Current = NULL;
	CStudent* temp = NULL;

	CHashTable<CStudent>* hash = NULL;

	if (List == NULL) {
		printf("\n�����Ͱ� �����ϴ�\n");
		return 0;
	}

	printf("�̸����� �˻� �����մϴ�. �̸��� �Է����ּ��� > ");
	scanf("%s", name);


	hash = hash->CreateHashTable(10);
	/////////////////////////////////
	
	if (List != NULL)
	Count = m_list_manage.countNodes(List);

	for (i = 0; i<Count; i++)
	{
		temp = m_list_manage.findNode(List, i);
		hash->Set(hash, &temp);
	}
	

	return hash->Get(hash, name);
	
	/////////////////////////////////
	hash->DestroyHashTable(hash);

	return 0;

	/*
	int i = 0, Count = 0;

	char name[10] = { 0 };   //�̸�
	int eng = 0;            //����
	int math = 0;           //����
	int sci = 0;            //����
	int classroom = 0;      //�ݹ�ȣ

	CStudent* Current = NULL;


	if (List == NULL) {
		printf("\n�����Ͱ� �����ϴ�\n");
		return 0;
	}		
	printf("�̸����� �˻� �����մϴ�. �̸��� �Է����ּ��� > ");
	scanf("%s", name);
	
	if (List != NULL)
		Count = m_list_manage.countNodes(List);

	for (i = 0; i<Count; i++)
	{
		Current = m_list_manage.findNode(List, i);

		if (strcmp(Current->Name, name) == 0)
			return Current;
	}
	return 0;
	*/
	return 0;
}
CStudent* CStudentManagement::eraseAll(CStudent* List)	 //10.������ ����
{
	int   i = 0;
	int   Count = 0;
	CStudent* Current = NULL;

	Count = m_list_manage.countNodes(List);

	for (i = 0; i<Count; i++)
	{
		Current = m_list_manage.findNode(List, 0);

		if (Current != NULL)
		{
			m_list_manage.removeNode(&List, Current);
			m_list_manage.destroyNode(Current);
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
		case PRINTALL:    //1.��� ���
			printResult(m_List);
			break;
		case FILESAVE:	  //2.���Ϸ� ����(to ����)
			saveToFile(m_List);
			break;
		case FILELOAD:	  //3.�ε��ϱ� (from ����)
			m_List = eraseAll(m_List);
			loadToFile( &m_List);
			break;
		case INPUTDATA:	  //4.���� �Է�
			inputData(m_List);
			break;
		case INPUTMAN:	  //5.�ο� �߰�
			inputMan(&m_List);
			break;
		case DELDATA:	  //6.�ο� ����
			delData(m_List);
			break;
		case SORTDATA:	  //7.�ο� ����
			sortData(&m_List);
			getchar();
			getchar();
			break;
		case FINDMAN:	  //8.�ο� �˻�
			m_Current = (CStudent*)findMan(m_List);
			if (m_Current != NULL) {
				printf("=====================���===================\n");
				printf("�̸�\t����\t����\t����\t����\t����\t��\t��ȣ\n");
				printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", m_Current->Name, m_Current->eng, m_Current->math, m_Current->sci, m_Current->total, m_Current->ranks, m_Current->classroom, m_Current->num);
			}
			g_iMenuNum = FIRSTSCREEN;
			getchar();
			getchar();

			break;
		case QUITPROG:	  //9.���α׷� ����
			break;
		case ERASEALL:    //10.������ ����
			m_List = eraseAll(m_List);
			printf("\n������ ������ �Ϸ� �Ǿ����ϴ�\n");
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
		case PRINTALL:    //1.��� ���
			printResult(*m_List);
			break;
		case FILESAVE:	  //2.���Ϸ� ����(to ����)
			saveToFile(*m_List);
			break;
		case FILELOAD:	  //3.�ε��ϱ� (from ����)
			m_List = eraseAll(m_List);
			loadToFile(&m_List);
			break;
		case INPUTDATA:	  //4.���� �Է�
			inputData(*m_List);
			break;
		case INPUTMAN:	  //5.�ο� �߰�
			inputMan(&m_List);
			break;
		case DELDATA:	  //6.�ο� ����
			delData(m_List);
			break;
		case SORTDATA:	  //7.�ο� ����
			sortData(&m_List);
			getchar();
			getchar();
			break;
		case FINDMAN:	  //8.�ο� �˻�
			m_Current = findMan(m_List);
			if (m_Current != NULL) {
				printf("=====================���===================\n");
				printf("�̸�\t����\t����\t����\t����\t����\t��\t��ȣ\n");
				printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", m_Current->Name, m_Current->eng, m_Current->math, m_Current->sci, m_Current->total, m_Current->ranks, m_Current->classroom, m_Current->num);
			}
			g_iMenuNum = FIRSTSCREEN;
			getchar();
			getchar();

			break;
		case QUITPROG:	  //9.���α׷� ����
			break;
		case ERASEALL:    //10.������ ����
			m_List = eraseAll(m_List);
			printf("\n������ ������ �Ϸ� �Ǿ����ϴ�\n");
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
	/*  ����Ʈ ��� */
	int   i = 0;
	int   Count = 0;
	CStudent* Current = NULL;

	//if (List != NULL)
		Count = m_list_manage.countNodes(&List);


	printf("=====================���===================\n");
	printf("�̸�\t����\t����\t����\t����\t����\t��\t��ȣ\n");

	//if (List == NULL)
	//	printf("\n�����Ͱ� �����ϴ�\n");

	for (i = 0; i<Count; i++)
	{
		Current = (CStudent*)m_list_manage.findNode(&List, i);

		if (Current != NULL)
			printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Current->Name, Current->eng, Current->math, Current->sci, Current->total, Current->ranks, Current->classroom, Current->num);

	}
	getchar();
	getchar();
	g_iMenuNum = FIRSTSCREEN;

} //1.��ü ���

void CStudentManagement::saveToFile(CStudent& List) const {
	int   i = 0, Count = 0;
	CStudent* Current = NULL;
	char buffer[256] = { 0 };
	char buffer2[256] = { 0 };
	FILE *f;

	Count = m_list_manage.countNodes(&List);

	f = fopen("StudentData.dat", "wt");


	fprintf(f, buffer);

	for (i = 0; i<Count; i++)
	{
		Current = m_list_manage.findNode(&List, i);

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

	printf("\n���̺갡 �Ϸ� �Ǿ����ϴ�\n");
	getchar();
	getchar();

	g_iMenuNum = FIRSTSCREEN;

}  //2.���Ϸ� ���� 

//void CStudentManagement::loadToFile(Node** List) {}//3.���Ϸ� ���� �о��

int CStudentManagement::inputData(CStudent& List) {

	int i = 0, Count = 0;

	char name[10] = { 0 };   //�̸�
	int eng = 0;            //����
	int math = 0;           //����
	int sci = 0;            //����
	int classroom = 0;      //�ݹ�ȣ

	/*
	if (List == NULL) {
		printf("\n�����Ͱ� �����ϴ�\n");
		getchar();
		getchar();
		g_iMenuNum = FIRSTSCREEN;
		return 0;
	}
	*/

	CStudent* Current = NULL;

	Current = (CStudent*)findMan(&List);

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
	g_iMenuNum = FIRSTSCREEN;
	getchar();
	getchar();

	return 0;
} 	
