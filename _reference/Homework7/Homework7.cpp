//#include "stdafx.h"
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Node
{
	int iData;
	int iIndex;
	Node* pChild[2];
};
Node* g_pRootNode = 0;
int g_iIndex = 0;
Node* g_pArray[16];
Node* Find(Node* pNode, int iValue)
{
	if (pNode == NULL)return NULL;
	if (pNode->iIndex == iValue)
	{
		return pNode;
	}
	for (int iChild = 0; iChild < 2; iChild++)
	{
		Node* pFind = Find(pNode->pChild[iChild], iValue);
		if (pFind != NULL) return pFind;
	}
	return NULL;
}
Node* NewNode(int iValue)
{
	Node* pNode = new Node;
	g_pArray[g_iIndex];
	pNode->iData = iValue;
	pNode->iIndex = g_iIndex++;
	pNode->pChild[0] = 0;
	pNode->pChild[1] = 0;
	return pNode;
}
void PrintNode(Node* pNode)
{
	if (pNode == NULL) return;
	//printf("%d  ", pNode->iIndex);
	PrintNode(pNode->pChild[0]);
	//printf("%d  ", pNode->iIndex);
	PrintNode(pNode->pChild[1]);
	printf("%d  ", pNode->iIndex);
}
void AddNode(int iValue)
{
	//노드 생성
	Node* pNode = NewNode(iValue);
	//2진 트리 구축
	Node* pParent = Find(g_pRootNode, (pNode->iIndex - 1) / 2);
	//Node* pParent = g_pArray[(pNode->iIndex - 1) / 2];
	if (pParent->pChild[0] == NULL)
	{
		pParent->pChild[0] = pNode;
	}
	else
	{
		pParent->pChild[1] = pNode;
	}
}
void SetData(int Array[], int iCnt)
{
	time_t tmp = clock();
	unsigned int iTick = rand();
	srand((unsigned int)time(&tmp));
	for (int i = 0; i < iCnt; i++)
	{
		Array[i] = (iTick + rand()) % iCnt;
	}
}


int main()
{
	const int MAX_CNT = 300;
	int iData[MAX_CNT];
	SetData(iData, MAX_CNT);
	g_pRootNode = NewNode(iData[0]);
	for (int iCnt = 1; iCnt < MAX_CNT; iCnt++)
	{
		AddNode(iData[iCnt]);
	}
	PrintNode(g_pRootNode);
	return 0;
}
*/

#include <stdio.h>

struct Node {
	int iIndex;
	int* pLeft;
	int* pRight;
};

Node* newNode(Node* root) {
	Node* newnode;

	if (root == NULL) {
		root = new Node;
		return root;

	}
	else {
		newNode->pLeft = new Node;
		return 
	}

}
Node* addNode(Node* root);
Node* findNode(Node* root);
void printNodes(Node* root);
void setData(Node* root);

Node* g_root_node = NULL;

void main() {
	//level order로 삽입
	g_root_node = new Node;

	
	//pre order로 순회




	delete g_root_node;
}