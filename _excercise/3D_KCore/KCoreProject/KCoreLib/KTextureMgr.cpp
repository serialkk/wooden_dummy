#include "KTextureMgr.h"

int KTextureMgr::Load( T_STR fileName )
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
		
		KTexture* pImage;
		for( TItor itor = m_Map.begin(); 
		 itor != m_Map.end();
		 itor++ )
		{
			pImage = (KTexture*)(*itor).second;
			
			if( !_tcsicmp(pImage->m_strName.c_str(),
				szFileName ))
			{
				return (*itor).first;
			}
		}


	}
	KTexture* pImage = new KTexture;
	if( pImage == NULL ) return -1;
	pImage->Init();
	pImage->m_strName = szFileName;
	pImage->Load(fileName );

	m_Map.insert( make_pair(++m_iCurIndex,
						    pImage) );
	return m_iCurIndex;

}
KTexture* KTextureMgr::GetPtr( int iIndex )
{
	TItor itor = m_Map.find( iIndex );
	if( itor == m_Map.end() ) return NULL;
	KTexture* pImage = (*itor).second;
	return pImage;
}
KTextureMgr::KTextureMgr(void)
{
	m_iCurIndex = 0;
}

bool	KTextureMgr::Init()
{
	return true;
}

bool	KTextureMgr::Frame(){
	return true;
}
bool	KTextureMgr::Render(){
	return true;
}
bool	KTextureMgr::Release(){
	KTexture* pImage;
	for( TItor itor = m_Map.begin(); 
		 itor != m_Map.end();
		 itor++ )
	{
		pImage = (KTexture*)(*itor).second;
		pImage->Release();
		delete pImage;
	}
	m_Map.clear();
	return true;
}
KTextureMgr::~KTextureMgr(void)
{
}
