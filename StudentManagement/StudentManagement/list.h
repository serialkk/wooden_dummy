#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

template <typename T>
class CList {

	//멤버변수
public:
	//멤버함수
	T* createNode(T NewData);
	void  destroyNode(T* Node);
	void  appendNode(T** Head, T* NewNode);
	void  insertAfter(T* Current, T* NewNode);
	//void  insertNewHead(T** Head, T* NewHead);
	void  removeNode(T** Head, T* Remove);
	T* findNode(T* Head, int Location) const;
	int   countNodes(T* Head) const;

};
template <typename T>
T* CList<T>::createNode(T NewData)
{
	T* node = new T;
	*node = NewData;
	return node;
}


template <typename T>
void CList<T>::destroyNode(T* Node)
{
	delete Node;
}

template <typename T>
void CList<T>::appendNode(T** Head, T* NewNode)
{

	if ((*Head) == NULL)
	{
		*Head = NewNode;
	}
	else
	{
		T* Tail = (*Head);
		while (Tail->NextNode != NULL)
		{
			Tail = Tail->NextNode;
		}

		Tail->NextNode = NewNode;
		NewNode->PrevNode = Tail;
	}
}

template <typename T>
void CList<T>::insertAfter(T* Current, T* NewNode)
//{
//	NewNode->NextNode = Current->NextNode;
//	Current->NextNode = NewNode;
//}

{
	NewNode->NextNode = Current->NextNode;
	NewNode->PrevNode = Current;

	if (Current->NextNode != NULL)
	{
		Current->NextNode->PrevNode = NewNode;
		Current->NextNode = NewNode;
	}
}
//template <typename T>
//void  CList<T>::insertNewHead(T** Head, T* NewHead)
//{
//	if (Head == NULL)
//	{
//		(*Head) = NewHead;
//	}
//	else
//	{
//		NewHead->NextNode = (*Head);
//		(*Head) = NewHead;
//	}
//}

template <typename T>
void CList<T>::removeNode(T** Head, T* Remove)
//{
//	if (*Head == Remove)
//	{
//		*Head = Remove->NextNode;
//	}
//	else
//	{
//		T* Current = *Head;
//		while (Current != NULL && Current->NextNode != Remove)
//		{
//			Current = Current->NextNode;
//		}
//
//		if (Current != NULL)
//			Current->NextNode = Remove->NextNode;
//	}
//}

{
	if (*Head == Remove)
	{
		*Head = Remove->NextNode;
		if ((*Head) != NULL)
			(*Head)->PrevNode = NULL;

		Remove->PrevNode = NULL;
		Remove->NextNode = NULL;
	}
	else
	{
		T* Temp = Remove;

		if (Remove->PrevNode != NULL)
			Remove->PrevNode->NextNode = Temp->NextNode;

		if (Remove->NextNode != NULL)
			Remove->NextNode->PrevNode = Temp->PrevNode;

		Remove->PrevNode = NULL;
		Remove->NextNode = NULL;
	}
}

template <typename T>
T* CList<T>::findNode(T* Head, int Location) const
{
	T* Current = Head;

	while (Current != NULL && (--Location) >= 0)
	{
		Current = Current->NextNode;
	}

	return Current;
}

template <typename T>
int CList<T>::countNodes(T* Head) const
//{
//	int   Count = 0;
//	T* Current = Head;
//
//	while (Current != NULL)
//	{
//		Current = Current->NextNode;
//		Count++;
//	}
//
//	return Count;
//}

{
	unsigned int  Count = 0;
	T*         Current = Head;

	while (Current != NULL)
	{
		Current = Current->NextNode;
		Count++;
	}

	return Count;
}



class CNode {
public:

	CNode* NextNode;//자기참조 구조체

	virtual void print_to_buffer(char* buffer, int size);


};

class CStudent : public CNode {
public:
	char Name[10];	//이름
	int eng;		//영어
	int math;		//수학
	int sci;		//과학
	int total;		//총점
	int ranks;		//석차
	int classroom;	//반
	int num;

	CStudent* PrevNode;
	CStudent* NextNode;//자기참조 구조체

					   // = 연산자 연산자 재정의
	CStudent operator=(const CStudent& node);

	void print_to_buffer(char * buffer, int size);
	friend ostream& operator << (ostream &os, const CStudent& p);
	friend istream& operator >> (istream &is, CStudent& p);

};

#endif
