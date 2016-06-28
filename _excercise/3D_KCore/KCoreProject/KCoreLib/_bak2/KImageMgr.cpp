#include "KImageMgr.h"

int KImageMgr::Load( HWND hWnd, 
					 HDC hdc,
	T_STR fileName )
{
	// 중복 제거
	TCHAR Dirve[MAX_PATH] = {0, };
	TCHAR Dir[MAX_PATH] = {0, };
	TCHAR Name[MAX_PATH] = {0, };
	TCHAR Ext[MAX_PATH] = {0, };
	TCHAR szFileName[MAX_PATH] = {0, };

	if( !fileName.empty() )
	{
		_tsplitpath_s( fileName.c_str(),
			Dirve, Dir, Name, Ext );
		_stprintf_s( szFileName, _T("%s%s"),
			Name, Ext );
		
		KImage* pImage;
		for( TItor itor = m_Map.begin(); 
		 itor != m_Map.end();
		 itor++ )
		{
			pImage = (KImage*)(*itor).second;
			
			if( !_tcsicmp(pImage->m_strName.c_str(),
				szFileName ))
			{
				return (*itor).first;
			}
		}


	}
	KImage* pImage = new KImage;
	if( pImage == NULL ) return -1;
	pImage->Init();
	pImage->m_strName = szFileName;
	pImage->Load( hWnd, hdc, fileName );

	m_Map.insert( make_pair(++m_iCurIndex,
						    pImage) );
	return m_iCurIndex;

}
KImage* KImageMgr::GetPtr( int iIndex )
{
	TItor itor = m_Map.find( iIndex );
	if( itor == m_Map.end() ) return NULL;
	KImage* pImage = (*itor).second;
	return pImage;
}
KImageMgr::KImageMgr(void)
{
	m_iCurIndex = 0;
}

bool	KImageMgr::Init()
{
	return true;
}

bool	KImageMgr::Frame(){
	return true;
}
bool	KImageMgr::Render(){
	return true;
}
bool	KImageMgr::Release(){	
	KImage* pImage;
	for( TItor itor = m_Map.begin(); 
		 itor != m_Map.end();
		 itor++ )
	{
		pImage = (KImage*)(*itor).second;
		pImage->Release();
		delete pImage;
	}
	m_Map.clear();
	return true;
}
KImageMgr::~KImageMgr(void)
{
}
