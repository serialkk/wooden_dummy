#pragma once
#include "TTexture.h"
class TTextureMgr : public TSingleton<TTextureMgr>
{
private:
	friend class TSingleton<TTextureMgr>;
public:
	typedef std::map<int, TTexture*>::iterator TItor;
	map<int, TTexture*>   m_Map;
	int					m_iCurIndex;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int	  Load(	T_STR strLoadFile);
	TTexture*    GetPtr( int iIndex );

private:
	TTextureMgr(void);
	~TTextureMgr(void);
};
#define I_TexMgr TTextureMgr::GetInstance()
