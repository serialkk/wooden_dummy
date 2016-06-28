#pragma once
#include "KTexture.h"
class KTextureMgr : public KSingleton<KTextureMgr>
{
private:
	friend class KSingleton<KTextureMgr>;
public:
	typedef std::map<int, KTexture*>::iterator TItor;
	map<int, KTexture*>   m_Map;
	int					m_iCurIndex;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int	  Load(	T_STR strLoadFile);
	KTexture*    GetPtr( int iIndex );

private:
	KTextureMgr(void);
	~KTextureMgr(void);
};
#define I_TexMgr KTextureMgr::GetInstance()
