#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode
{
	char name;
	ElementType iData;
	struct tagNode* PrevNode;
	struct tagNode* NextNode;
} Node;

Node* createNode(ElementType NewData);
void  destroyNode(Node* Node);
void  appendNode(Node** Head, Node* NewNode);
void  insertAfter(Node* Current, Node* NewNode);
void  removeNode(Node** Head, Node* Remove);
Node* getNodeAt(Node* Head, int Location);
Node* getNodeAt2(Node* Head, int Location,int position);
int   getNodeCount(Node* Head);

