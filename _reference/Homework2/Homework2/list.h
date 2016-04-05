#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

/*
typedef struct tagNode
{
	ElementType Data;
	struct tagNode* NextNode;
} Node;
*/
typedef struct student {
	char Name[10];	//�̸�
	int eng;		//����
	int math;		//����
	int sci;		//����
	int total;		//����
	int ranks;		//����
	int classroom;	//��
	int num;		//��ȣ

	struct student* NextNode;
} Node;

/* �Լ� ���� ���� */
Node* createNode(student NewData);
void  destroyNode(Node* Node);
void  appendNode(Node** Head, Node* NewNode);
void  insertAfter(Node* Current, Node* NewNode);
void  insertNewHead(Node** Head, Node* NewHead);
void  removeNode(Node** Head, Node* Remove);
Node* getNodeAt(Node* Head, int Location);
int   getNodeCount(Node* Head);

#endif
