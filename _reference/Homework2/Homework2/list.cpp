#include "list.h"
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

//��� ����
Node* createNode(Node NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	// ������ ����
	NewNode->num = NewData.num;  
	NewNode->classroom = NewData.classroom;
	NewNode->eng = NewData.eng;
	NewNode->math= NewData.math;
	strcpy(NewNode->Name,NewData.Name);
	//NewNode->NextNode = NewData.NextNode;
	NewNode->num = NewData.num;
	NewNode->ranks = NewData.ranks;
	NewNode->sci = NewData.sci;
	NewNode->total = NewData.total;





	NewNode->NextNode = NULL; //  ���� ��忡 ���� �����ʹ� NULL�� �ʱ�ȭ �Ѵ�. 

	return NewNode;//  ����� �ּҸ� ��ȯ�Ѵ�.
}

//  ��� ����
void destroyNode(Node* Node)
{
	free(Node);
}

//  ��� �߰�
void appendNode(Node** Head, Node* NewNode)
{
	/*  ��� ��尡 NULL�̶�� ���ο� ��尡 Head */
	if ((*Head) == NULL)
	{
		*Head = NewNode;
	}
	else
	{
		/*  ������ ã�� NewNode�� �����Ѵ�. */
		Node* Tail = (*Head);
		while (Tail->NextNode != NULL)
		{
			Tail = Tail->NextNode;
		}

		Tail->NextNode = NewNode;
	}
}

/*  ��� ���� */
void insertAfter(Node* Current, Node* NewNode)
{
	NewNode->NextNode = Current->NextNode;
	Current->NextNode = NewNode;
}

void  insertNewHead(Node** Head, Node* NewHead)
{
	if (Head == NULL)
	{
		(*Head) = NewHead;
	}
	else
	{
		NewHead->NextNode = (*Head);
		(*Head) = NewHead;
	}
}

/*  ��� ���� */
void removeNode(Node** Head, Node* Remove)
{
	if (*Head == Remove)
	{
		*Head = Remove->NextNode;
	}
	else
	{
		Node* Current = *Head;
		while (Current != NULL && Current->NextNode != Remove)
		{
			Current = Current->NextNode;
		}

		if (Current != NULL)
			Current->NextNode = Remove->NextNode;
	}
}

/*  ��� Ž�� */
Node* getNodeAt(Node* Head, int Location)
{
	Node* Current = Head;

	while (Current != NULL && (--Location) >= 0)
	{
		Current = Current->NextNode;
	}

	return Current;
}

/*  ��� �� ���� */
int getNodeCount(Node* Head)
{
	int   Count = 0;
	Node* Current = Head;

	while (Current != NULL)
	{
		Current = Current->NextNode;
		Count++;
	}

	return Count;
}
