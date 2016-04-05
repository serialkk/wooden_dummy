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
	char Name[10];	//이름
	int eng;		//영어
	int math;		//수학
	int sci;		//과학
	int total;		//총점
	int ranks;		//석차
	int classroom;	//반
	int num;		//번호

	struct student* NextNode;
} Node;

/* 함수 원형 선언 */
Node* createNode(student NewData);
void  destroyNode(Node* Node);
void  appendNode(Node** Head, Node* NewNode);
void  insertAfter(Node* Current, Node* NewNode);
void  insertNewHead(Node** Head, Node* NewHead);
void  removeNode(Node** Head, Node* Remove);
Node* getNodeAt(Node* Head, int Location);
int   getNodeCount(Node* Head);

#endif
