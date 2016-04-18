#pragma once
#include "TSprite.h"
#include <map>
//pair<key, data>
class TSpriteMgr : public TSingleton<TSpriteMgr>
{
private:
	INT			m_iKey;
	friend class TSingleton<TSpriteMgr>;
	std::map<INT, TSprite*>   m_mapList;
	TSprite*   Load(TCHAR* pszLoadFile);
	TSprite*   Find(INT iKey);
public:
	TSpriteMgr();
	virtual ~TSpriteMgr();
};
#define I_Sprite TSpriteMgr::GetInstance()
