#include "List.h"

/*  노드 생성 */
Node* createNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->iData = NewData;
	NewNode->PrevNode = NULL;
	NewNode->NextNode = NULL;

	return NewNode;
}

/*  노드 소멸 */
void destroyNode(Node* Node)
{
	free(Node);
}

/*  노드 추가 */
void appendNode(Node** Head, Node* NewNode)
{
	/*  헤드 노드가 NULL이라면 새로운 노드가 Head */
	if ((*Head) == NULL)
	{
		*Head = NewNode;
		(*Head)->NextNode = *Head;
		(*Head)->PrevNode = *Head;
	}
	else
	{
		/*  테일과 헤드 사이에 NewNode를 삽입한다. */
		Node* Tail = (*Head)->PrevNode;

		Tail->NextNode->PrevNode = NewNode;
		Tail->NextNode = NewNode;

		NewNode->NextNode = (*Head);
		NewNode->PrevNode = Tail; /*  기존의 테일을 새로운  */
								  /*  테일의 PrevNode가 가리킨다. */
	}
}

/*  노드 삽입 */
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

/*  노드 제거 */
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

/*  노드 탐색 */
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

/*  노드 수 세기 */
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
