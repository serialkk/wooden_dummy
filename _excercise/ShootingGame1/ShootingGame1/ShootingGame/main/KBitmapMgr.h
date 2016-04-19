#pragma once
#include "KHashTable.h"
#include "KBitmap.h"
class KBitmapMgr : public KSingleton<KBitmapMgr>
{
public:
	friend class KSingleton<KBitmapMgr>;
	/*static KBitmapMgr& GetInstance()
	{
		static KBitmapMgr  mgr;
		return mgr;
	}*/
public:
	KLinkedList<KBitmap>   m_List;
	KHashTable<KBitmap>    m_Hash;
private:
	KLinkedList<KBitmap>   m_InitList;
public:
	KBitmap*  Load(TCHAR* pszLoadFile);
	KBitmap*  Find(int iIndex);
	void    Sort(bool bUp = true);
	void    Release();
	void    ShowData();
	void    ShowData(KBitmap* pStd);
	void    Delete(int iIndex) {};
	void    Delete(KBitmap* iData) {};
	KNode<KBitmap> * Swap(
		KNode<KBitmap>* a,
		KNode<KBitmap>* b);
	KBitmap*  Find(TCHAR* pszName);
public:
	KBitmapMgr();
public:
	~KBitmapMgr();
};
#define I_BimapMgr KBitmapMgr::GetInstance()
