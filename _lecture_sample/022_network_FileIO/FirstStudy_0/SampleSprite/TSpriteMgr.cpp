#include "TSpriteMgr.h"

INT  TSpriteMgr::Load(TCHAR* pszName,
	TCHAR* pszColorFile,
	TCHAR* pszMaskFile)
{
	// 중복체크
	TSprite* pSprite = new TSprite;
	if( !pSprite->Load(pszColorFile, pszMaskFile) )
	{
		delete pSprite;
		return 0;
	}
	pSprite->m_szName = pszName;
	m_mapList.insert( make_pair(++m_iKey, pSprite));
	pSprite->m_iSpriteID = m_iKey;
	return m_iKey;
}
TSprite*  TSpriteMgr::Find(INT iKey)
{
	std::map<INT, TSprite*>::iterator itor= 
					m_mapList.find(iKey);
	if (itor == m_mapList.end()) return NULL;
	//TSprite* pSprite = (*itor).first; // key
	TSprite* pSprite = (*itor).second;// data
	return pSprite;
}

TSpriteMgr::TSpriteMgr()
{
	m_iKey = 0;
}


TSpriteMgr::~TSpriteMgr()
{
}
