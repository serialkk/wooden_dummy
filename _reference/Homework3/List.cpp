#include "List.h"

/*  ��� ���� */
Node* createNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->iData = NewData;
	NewNode->PrevNode = NULL;
	NewNode->NextNode = NULL;

	return NewNode;
}

/*  ��� �Ҹ� */
void destroyNode(Node* Node)
{
	free(Node);
}

/*  ��� �߰� */
void appendNode(Node** Head, Node* NewNode)
{
	/*  ��� ��尡 NULL�̶�� ���ο� ��尡 Head */
	if ((*Head) == NULL)
	{
		*Head = NewNode;
		(*Head)->NextNode = *Head;
		(*Head)->PrevNode = *Head;
	}
	else
	{
		/*  ���ϰ� ��� ���̿� NewNode�� �����Ѵ�. */
		Node* Tail = (*Head)->PrevNode;

		Tail->NextNode->PrevNode = NewNode;
		Tail->NextNode = NewNode;

		NewNode->NextNode = (*Head);
		NewNode->PrevNode = Tail; /*  ������ ������ ���ο�  */
								  /*  ������ PrevNode�� ����Ų��. */
	}
}

/*  ��� ���� */
void insertAfter(Node* Current, Node* NewNode)
{
	NewNode->NextNode = Current->NextNode;
	NewNode->PrevNode = Current;

	if (Current->NextNode != NULL)
	{
		Current->NextNode->PrevNode = NewNode;
		Current->NextNode = NewNode;
	}
}

/*  ��� ���� */
void removeNode(Node** Head, Node* Remove)
{
	if (*Head == Remove)
	{
		(*Head)->PrevNode->NextNode = Remove->NextNode;
		(*Head)->NextNode->PrevNode = Remove->PrevNode;

		*Head = Remove->NextNode;

		Remove->PrevNode = NULL;
		Remove->NextNode = NULL;
	}
	else
	{
		/*
		Node* Temp = Remove;

		Remove->PrevNode->NextNode = Temp->NextNode;
		Remove->NextNode->PrevNode = Temp->PrevNode;
		*/
		Remove->PrevNode->NextNode = Remove->NextNode;
		Remove->NextNode->PrevNode = Remove->PrevNode;

		Remove->PrevNode = NULL;
		Remove->NextNode = NULL;
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

Node* getNodeAt2(Node* Head, int Location,int position)
{
	Node* Current = Head;
	int i = 0;

	while (Current != NULL && (--Location) >= 0)
	{
		for (i = 0; i < position;i++)
			Current = Current->NextNode;

	}

	return Current;
}

/*  ��� �� ���� */
int getNodeCount(Node* Head)
{
	unsigned int  Count = 0;
	Node*         Current = Head;

	while (Current != NULL)
	{
		Current = Current->NextNode;
		Count++;

		if (Current == Head)
			break;
	}

	return Count;
}

void PrintNode(Node* _Node)
{
	if (_Node->PrevNode == NULL)
		printf("Prev: NULL");
	else
		printf("Prev: %d", _Node->PrevNode->iData);

	printf(" Current: %d ", _Node->iData);

	if (_Node->NextNode == NULL)
		printf("Next: NULL\n");
	else
		printf("Next: %d\n", _Node->NextNode->iData);
}
