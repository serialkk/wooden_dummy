#pragma once
#include "list.h"
#include "tchar.h"
typedef int KeyType;
typedef int ValueType;

//typedef struct tagNode
//{
//	KeyType   Key;
//	ValueType Value;
//} Node;

template <typename T>
class CHashTable
{

	int		m_iTableSize;
	T*		m_Table;
	CList<T> m_list_manage;

public:

	CHashTable();
	~CHashTable();

	CHashTable* CreateHashTable(int TableSize);
	void       Set(CHashTable* HT, T** node);
	T*  Get(CHashTable* HT, char* pName);
	void       DestroyHashTable(CHashTable* HT);
	int        Hash(KeyType Key, int TableSize);
	int        Hash(char* pName);
};

template <typename T>
CHashTable<T>::CHashTable()
{
}

template <typename T>
CHashTable<T>::~CHashTable()
{
}


template <typename T>
CHashTable<T>* CHashTable<T>::CreateHashTable(int TableSize)
{
	CHashTable* HT = (CHashTable*)malloc(sizeof(CHashTable));
	HT->m_Table = (T*)malloc(sizeof(T) * TableSize);
	memset(HT->m_Table, 0, sizeof(T)*TableSize);
	HT->m_iTableSize = TableSize;

	return HT;
}

/*
template <typename T>
void CHashTable<T>::Set(CHashTable* HT, KeyType Key, ValueType Value)
{
	int Address = Hash(Key, HT->m_iTableSize);

	HT->m_Table[Address].Key = Key;
	HT->m_Table[Address].Value = Value;
	
}
*/

template <typename T>
void CHashTable<T>::Set(CHashTable* HT, T** node)
{
	
	//int Address = Hash(Key, HT->m_iTableSize);
	int Address = Hash((*node)->Name);
	T* temp = &(HT->m_Table[Address]);

	T* NewNode = HT->m_list_manage.createNode(**node);
	HT->m_list_manage.appendNode(&temp, NewNode);

		/*
		HT->m_Table[Address].Key = Key;
		HT->m_Table[Address].Value = Value;
		*/
}
/*
template <typename T>
ValueType CHashTable<T>::Get(CHashTable* HT, KeyType Key)
{
	int Address = Hash(Key, HT->m_iTableSize);

	
	return HT->m_Table[Address].Value;
	
}
*/
template <typename T>
T* CHashTable<T>::Get(CHashTable* HT, char* pName)
{
	int i =0, Count = 0;
	T* Current = NULL;

	int Address = Hash(pName);

	if (HT->m_Table != NULL)
		Count = HT->m_list_manage.countNodes(&(HT->m_Table[Address]));

	for (i = 0; i < Count; i++) {
		Current = HT->m_list_manage.findNode(&(HT->m_Table[Address]), i);

		if (strcmp(Current->Name, pName) == 0)
			return Current;
	}

	return 0;
}

template <typename T>
void CHashTable<T>::DestroyHashTable(CHashTable* HT)
{
	free(HT->m_Table);
	free(HT);
}

template <typename T>
int CHashTable<T>::Hash(KeyType Key, int TableSize)
{
	return Key % TableSize;
}

template <typename T>
int CHashTable<T>::Hash(char* pName)
{
	int iValue = 0;
	int iLen = strlen(pName);
	for (int i = 0; i < iLen; i++)
	{
		iValue += pName[i];
	}

	int iKey = (iValue * iValue) % m_iTableSize; 
	return iKey;
}

//template <typename T>
//int CHashTable<T>::Hash(void* p)
//{
//	int iKey = reinterpret_cast<int>(p);
//	return (iKey ^ (iKey >> 16));
//}
