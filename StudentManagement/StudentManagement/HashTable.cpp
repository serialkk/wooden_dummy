#include "HashTable.h"
#include <stdlib.h>


CHashTable::CHashTable()
{
}


CHashTable::~CHashTable()
{
}



CHashTable* CHashTable::CreateHashTable(int TableSize)
{
	CHashTable* HT = (CHashTable*)malloc(sizeof(CHashTable));
	HT->Table = (Node*)malloc(sizeof(Node) * TableSize);
	HT->TableSize = TableSize;

	return HT;
}

void CHashTable::Set(CHashTable* HT, KeyType Key, ValueType Value)
{
	int Address = Hash(Key, HT->TableSize);

	HT->Table[Address].Key = Key;
	HT->Table[Address].Value = Value;
}

ValueType CHashTable::Get(CHashTable* HT, KeyType Key)
{
	int Address = Hash(Key, HT->TableSize);

	return HT->Table[Address].Value;
}

void CHashTable::DestroyHashTable(CHashTable* HT)
{
	free(HT->Table);
	free(HT);
}

int CHashTable::Hash(KeyType Key, int TableSize)
{
	return Key % TableSize;
}
