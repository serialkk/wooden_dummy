#include <cstdio>
#include <string.h>
#include <iostream> //malloc
#define VAR(X) int m_##X;
struct TData
{
	int Value;
	TData* pNext; // 자기참조구조체
};
TData* g_pLinkedList = 0;
TData* g_pTailList = 0;
TData* FindNode(int iValue )
{
	for (TData* pList = g_pLinkedList;
	pList != NULL;
		pList = pList->pNext)
	{
		if (pList->Value == iValue)
		{
			return pList;
		}
	}
	return NULL;
}
void AddFirst(TData* pAdd)
{
	if (g_pTailList != NULL)
	{
		g_pLinkedList = pAdd;
		g_pLinkedList->pNext = g_pTailList;
		g_pTailList = pAdd;
		return;
	}
	if (g_pLinkedList == NULL)
	{
		g_pLinkedList = pAdd;
		g_pTailList = pAdd;
		return;
	}
}
void AddLast(TData* pAdd)
{
	if (g_pTailList != NULL)
	{
		g_pTailList->pNext = pAdd;
		g_pTailList = pAdd;
		//g_pTailList->pNext = g_pLinkedList;
		return;
	}
	if (g_pLinkedList == NULL)
	{
		g_pLinkedList = pAdd;
		g_pTailList = pAdd;		
		return;
	}	
}
void DeleteList()
{
	TData* pList = g_pLinkedList;
	TData* pDelNext = 0;
	for (; pList != NULL;)
	{
		pDelNext = pList->pNext;
		free(pList);
		pList = pDelNext;
	}
}
void main()
{
	TData* data1 = (TData*)malloc(sizeof(TData));
	TData* data2 = (TData*)malloc(sizeof(TData));
	TData* data3 = (TData*)malloc(sizeof(TData));
	TData* data4 = (TData*)malloc(sizeof(TData));
	data1->Value = 100;
	data1->pNext = 0;
	data2->Value = 200;
	data2->pNext = 0;
	data3->Value = 300;
	data3->pNext = 0;
	data4->Value = 400;
	data4->pNext = 0;

	AddFirst(data1);
	AddFirst(data2);
	AddFirst(data3);
	AddFirst(data4);

	/*AddLast(data1);
	AddLast(data2);
	AddLast(data3);
	AddLast(data4);*/
	
	for (TData* pList = g_pLinkedList;
	     pList != NULL;
	    pList = pList->pNext)
	{
		printf("\n%d",pList->Value );
	}

	printf("\nFind Node = %d", FindNode(200)->Value);
	DeleteList();
	getchar();
}