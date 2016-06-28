#pragma once
#include "KImage.h"
class KImageMgr : public KSingleton<KImageMgr>
{
private:
	friend class KSingleton<KImageMgr>;
public:
	typedef std::map<int,KImage*>::iterator TItor;
	map<int, KImage*>   m_Map;
	int					m_iCurIndex;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int	  Load(	HWND hWnd, 
				HDC hdc, 
		T_STR strLoadFile);
	KImage*    GetPtr( int iIndex );

private:
	KImageMgr(void);
	~KImageMgr(void);
};
#define I_ImageMgr KImageMgr::GetInstance()
