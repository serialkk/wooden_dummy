#pragma once
#include "list.h"
typedef int KeyType;
typedef int ValueType;

typedef struct tagNode
{
	KeyType   Key;
	ValueType Value;
} Node;

class CHashTable
{
public:
	int   TableSize;
	Node* Table;


	CHashTable();
	~CHashTable();

	CHashTable* CreateHashTable(int TableSize);
	void       Set(CHashTable* HT, KeyType Key, ValueType Value);
	ValueType  Get(CHashTable* HT, KeyType Key);
	void       DestroyHashTable(CHashTable* HT);
	int        Hash(KeyType Key, int TableSize);
};

