#include "List.h"
#include <string.h>


int main(void)
{
	int   i = 0, insert=0,interval=0;
	char mans[256] = { 0 };
	int   Count = 0;
	Node* List = NULL;
	Node* NewNode = NULL;
	Node* Current = NULL;
	Node* temp = NULL;

	printf("\n인원문자열? >");
	scanf("%s", mans);

	printf("\n간격? >");
	scanf("%d", &interval);

	while (true)
	{
		if(mans[insert] ==0)
			break;
		else { 
			insert++; 
		}
	}
	//printf("%s",strlen(mans));

	/*  노드 n개 추가 */
	for (i = 0; i<insert; i++)
	{
		NewNode = createNode(i);
		NewNode->name=mans[i];
		appendNode(&List, NewNode);
	}

	/*  리스트 출력 */
	Count = getNodeCount(List);
	for (i = 0; i<Count; i++)
	{
		Current = getNodeAt(List, i);
		printf("List[%d] : %d  %C\n", i, Current->iData, Current->name);
	}



	Count = getNodeCount(List);
	temp=Current = getNodeAt(List, 0);

	while (Current->NextNode!= Current) {
		
		for (i = 0; i < interval-1; i++) {
			temp = Current;
			Current = Current->NextNode;
		}
		temp->NextNode = Current->NextNode;

		printf("%c ", Current->name);
		
		if (Current != NULL)
		{
			removeNode(&List, Current);
			destroyNode(Current);
		}
		Current = temp->NextNode;

		if (Current->NextNode == Current)
			printf("\n마지막 생존자: %c ", Current->name);

	}



	/*
	Count = getNodeCount(List);
	for (i = 0; i<Count; i++)
	{
		Current = getNodeAt(List, i);
		printf("List[%d] : %d  %C\n", i, Current->iData, Current->name);
	}
	*/
	return 0;
}
