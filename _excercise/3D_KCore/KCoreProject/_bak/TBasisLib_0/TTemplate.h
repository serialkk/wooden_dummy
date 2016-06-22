#pragma once
#include "TDefine.h"

namespace TBASIS_BASE {

template< typename T > void Swap( T* a, T* b )
{
	T Temp;
	Temp = *a;
	*a = *b;
	*b = Temp;
}

template<class T> class TSingleton
{		
public:
	static T& GetInstance() 
	{		
		static T theSingleInstance;  
		return theSingleInstance; 
	}
	static T* GetInstancePtr() 
	{
		static T theSingleInstance; 
		return &theSingleInstance; 
	}
};
template<typename TContainer>
inline void stl_wipe(TContainer& container)
{
	for( TContainer::iterator i = container.begin() ; i != container.end() ; ++i )
		delete *i;
	container.clear();
}

template<typename T>
void stl_wipe_vector(vector<T>& rVector)
{
	vector<T> emptyData;
	rVector.swap( emptyData );
}

template<class T> class TSINGLETON
{
private:
	static T* m_pInstance;
public:
	TSINGLETON()	{	m_pInstance = (T*)this; }
	~TSINGLETON()	{	m_pInstance = 0; }
	static T& GetInstance()		{	return (*m_pInstance ); }
	static T* GetInstancePtr()	{	return m_pInstance;		}
};
template <class T> T* TSINGLETON<T>::m_pInstance = 0;


template< class Child, class Parent, int N > 
class TTemplate
{
public:	
	typedef map <INT, Child*>					TemplateMap;
	typedef typename TemplateMap::iterator		TemplateMapItor;	
	TemplateMapItor								TItor;
	TemplateMap									TMap;
	INT											m_iCurIndex;
public:
	bool		Init();
	INT			Clone( INT iIndex );
	INT			UniqueInsertPoint( Child* pChild, TCHAR *pFileName, TCHAR* szPath );
	INT			Add(Child*);
	INT			Add( TCHAR *pFileName, TCHAR* szPath = 0 );
	INT			AddObj( TCHAR *pFileName, TCHAR* szPath = 0 , bool bUniqueVertex = false,
							bool bNormalMap= false, 					 
							bool bEnvironment= false,
							int iSpeed = 1 );
	INT			Find( TCHAR *pFileName, TCHAR* szPath = 0 );	
	INT			AddPoint( Child* pChild, Parent* pParent, TCHAR *pFileName);
	Child*		GetPtr( INT index );
	Child*		GetPtr( TCHAR* szName );
	INT			GetID( Child* );
	INT			GetID( TCHAR* szName );
	bool		Frame();
	bool		Frame( float );
	bool		Render();
	INT			Count();
	bool		SetSpeed( float );
	bool		Render(Parent*);
	bool		SetReActive( bool bActive = false);
	bool		Release();
	bool		ResetDevice();
	// Delete하지 않고 리스트만 비운다.( 할당한 객체가 아닐경우 사용됨 : 포인터 대입의 경우 )
	bool		Clear();
	bool		SelDelete(Child *pPoint );
	bool		SelDelete(INT index );

	//bool		GetInform( TcInform& InForm );

public:
	TTemplate();
	~TTemplate();
};
template < class Child, class Parent, int N > 
INT TTemplate< Child, Parent, N >::GetID( Child* pChild )
{
	INT iIndex = 0;
	for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++) 
	{
		Child *pPoint = (Child *)(*itor).second;
		if( pChild == pPoint )  
		{
			iIndex =  (*itor).first;
			break;
		}
	}
	return iIndex;
}
template < class Child, class Parent, int N > 
INT TTemplate< Child, Parent, N >::GetID( TCHAR* szName )
{
	INT iIndex = -1;
	for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++) 
	{
		Child *pPoint = (Child *)(*itor).second;		
		if( !_tcsicmp( pPoint->m_szName.c_str(), szName ) )
		{		
			iIndex =  (*itor).first;
			break;
		}
	}
	return iIndex;
}
template < class Child, class Parent, int N > 
TTemplate< Child, Parent, N >::TTemplate()
{
	m_iCurIndex = 0;	
	TMap.clear();
	//Init();
}

template < class Child, class Parent, int N > 
TTemplate< Child, Parent, N >::~TTemplate()
{
	Child *pPoint;
	for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++ ) 
	{
		pPoint = (Child *)(*itor).second;
		pPoint->Release();
		SAFE_DEL(pPoint);
	}
	TMap.clear();
	m_iCurIndex = 0;
	//Release();
}


template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::SetSpeed( float fSpeed )
{
	Child *pPoint;
	for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++ ) 
	{
		pPoint = (Child *)(*itor).second;
		if( pPoint )
			pPoint->SetSpeed(fSpeed);
		else
			return false;

	}
	return true;
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::Init()
{
	m_iCurIndex = 0;	
	TMap.clear();
	return true;
}
template < class Child, class Parent, int N > 
INT TTemplate< Child, Parent, N >::Count()
{
	return (INT)TMap.size();
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::Release()
{
	Child *pPoint;
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++ ) 
	{
		pPoint = (Child *)(*itor).second;
		if( pPoint )
			pPoint->Release();
		else
			return false;
		SAFE_DEL(pPoint);
	}
	TMap.clear();
	m_iCurIndex = 0;
	return true;
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::Clear()
{
	Child *pPoint;
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++ ) 
	{
		pPoint = (Child *)(*itor).second;
		if( pPoint )
			pPoint->Release();
		else
			return false;		
	}
	TMap.clear();
	return true;
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::ResetDevice()
{
	Child *pPoint;
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++ ) 
	{
		pPoint = (Child *)(*itor).second;
		if( pPoint )
			pPoint->ResetDevice();
		else
			return false;		
	}	
	return true;
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::SelDelete(INT iIndex )
{
	Child *pPoint = GetPtr( iIndex );
	if( pPoint )
	{
		pPoint->Release();	
		TMap.erase(iIndex);
	}
	return true;
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::SelDelete(Child *pPoint )
{	
	if( pPoint )
	{
		pPoint->Release();
		TMap.erase(GetID(pPoint));
	}
	return true;
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::Frame()
{
	Child *pPoint;
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++ ) 
	{
		pPoint = (Child *)(*itor).second;
		if( pPoint )
			pPoint->Frame();
		else
			return false;		
	}	
	return true;
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::SetReActive( bool bActive )
{
	Child *pPoint;
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++ ) 
	{
		pPoint = (Child *)(*itor).second;
		if( pPoint )
			pPoint->SetReActive( bActive );
		else
			return false;
	}	
	return true;
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::Frame( float fElapsedTime )
{
	Child *pPoint;
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++ ) 
	{
		pPoint = (Child *)(*itor).second;
		if( pPoint )
			pPoint->Frame( fElapsedTime );
		else
			return false;	
	}	
	return true;
}
template < class Child, class Parent, int N > 
INT TTemplate< Child, Parent, N >::Clone( INT iIndex )
{
	Child *pPoint = NULL;
	SAFE_NEW( pPoint, Child );	
	pPoint->Init();
	pPoint->SetModelIndex( iIndex );	
	TMap.insert( make_pair( ++m_iCurIndex, pPoint ) );
	return m_iCurIndex;
}
template < class Child, class Parent, int N > 
INT TTemplate< Child, Parent, N >::UniqueInsertPoint( Child* pChild, TCHAR *pFileName, TCHAR* szPath )
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];	
	if( pFileName )
	{										
		_tsplitpath( pFileName, Drive, Dir, FName, Ext );						
		Ext[4]= 0;	
		memset( szFileName, 0, sizeof(TCHAR) * MAX_PATH );
		_stprintf_s( szFileName, _T("%s%s"), FName, Ext );		

		for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++) 
		{
			Child *pPoint = (Child *)(*itor).second;
			if( !_tcsicmp( pPoint->m_szName.c_str(), szFileName ) ) 
			{
				return (*itor).first;
			}
		}
	}
	pChild->Init();	
	if( !pChild->Load( pFileName, szPath ) ) 
	{
		SAFE_DEL( pChild );	
		return 0;
	}
	pChild->m_szName = szFileName;

	TMap.insert( make_pair( ++m_iCurIndex, pChild ) );	
	return m_iCurIndex;
}
template < class Child, class Parent, int N > 
INT TTemplate< Child, Parent, N >::Add( Child* pChild )
{
	if( pChild == NULL )
	{
		return 0;
	}
	for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++) 
	{
		Child *pPoint = (Child *)(*itor).second;
		if( pPoint == pChild ) 
		{
			return 0;
		}
	}
	TMap.insert( make_pair( ++m_iCurIndex, pChild ) );
	return m_iCurIndex;
}
template < class Child, class Parent, int N > 
INT TTemplate< Child, Parent, N >::Add( TCHAR *pFileName, TCHAR* szPath )
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];									
	_tsplitpath( pFileName, Drive, Dir, FName, Ext );						
	Ext[4]= 0;	
	_stprintf_s( szFileName, _T("%s%s"), FName, Ext );
	if( !pFileName )
	{	
		return 0;
	}

	Child *pPoint = NULL;
	SAFE_NEW( pPoint, Child );	
	pPoint->Init();

	if( !pPoint->Load( pFileName, szPath ) ) 
	{
		SAFE_DEL( pPoint );	
		return 0;
	}
	pPoint->m_szName = szFileName;

	TMap.insert( make_pair( ++m_iCurIndex, pPoint ) );	
	return m_iCurIndex;
}
template < class Child, class Parent, int N > 
INT TTemplate< Child, Parent, N >::AddObj( TCHAR *pFileName, TCHAR* szPath, bool bUniqueVertex,
					   bool bNormalMap, 					 
					   bool bEnvironment,
					   int iSpeed )
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];									
	_tsplitpath( pFileName, Drive, Dir, FName, Ext );						
	Ext[4]= 0;	
	_stprintf_s( szFileName, _T("%s%s"), FName, Ext );
	if( !pFileName )
	{	
		return 0;
	}

	Child *pPoint = NULL;
	SAFE_NEW( pPoint, Child );	
	pPoint->Init();
	if( szPath != NULL )
	{
		pPoint->SetTexturePath( szPath );
	}
	if( !pPoint->Load( pFileName, szPath, bUniqueVertex, bNormalMap, bEnvironment,  iSpeed ) ) 
	{
		SAFE_DEL( pPoint );	
		return 0;
	}
	pPoint->m_szName = szFileName;

	TMap.insert( make_pair( ++m_iCurIndex, pPoint ) );	
	return m_iCurIndex;
}
template < class Child, class Parent, int N > 
INT TTemplate< Child, Parent, N >::Find( TCHAR *pFileName, TCHAR* szPath )
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];	
	if( pFileName )
	{										
		_tsplitpath( pFileName, Drive, Dir, FName, Ext );						
		Ext[4]= 0;	
		memset( szFileName, 0, sizeof(TCHAR) * MAX_PATH );
		_stprintf_s( szFileName, _T("%s%s"), FName, Ext );		

		for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++) 
		{
			Child *pPoint = (Child *)(*itor).second;
			if( !_tcsicmp( pPoint->m_szName.c_str(), szFileName ) ) 
			{
				return (*itor).first;
			}
		}
	}

	Child *pPoint = NULL;
	SAFE_NEW( pPoint, Child );	
	pPoint->Init();

	if( !pPoint->Load( pFileName, szPath ) ) 
	{
		SAFE_DEL( pPoint );	
		return 0;
	}

	
	pPoint->m_szName = szFileName;

	TMap.insert( make_pair( ++m_iCurIndex, pPoint ) );	
	return m_iCurIndex;
}
template < class Child, class Parent, int N > 
INT TTemplate< Child, Parent, N >::AddPoint( Child* pChild, Parent* pParent, TCHAR *pFileName)
{
	if(!pChild || !pParent ) return -1;
	pChild->Init();
	pChild->Create( pParent);

	TMap.insert( make_pair( ++m_iCurIndex, pChild ) );
	return m_iCurIndex;
}
template < class Child, class Parent, int N > 
Child *TTemplate< Child, Parent, N >::GetPtr( INT iIndex )
{
	TemplateMapItor itor = TMap.find(iIndex);
	if (itor == TMap.end()) return NULL;
	Child *pPoint = (*itor).second;	
	return pPoint;
}
template < class Child, class Parent, int N > 
Child* TTemplate< Child, Parent, N >::GetPtr( TCHAR* szName )
{
	for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++) 
	{
		Child *pPoint = (Child *)(*itor).second;
		if( !_tcsicmp( pPoint->m_szName.c_str(), szName ) ) 
		{
			return pPoint;
		}
	}
	return NULL;
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::Render()
{
	Child* pPoint = NULL;
	for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++ ) 
	{
		pPoint = (Child *)(*itor).second;
		if( pPoint )
		{
			pPoint->Render();			
		}
	}	
	return true;
}
template < class Child, class Parent, int N > 
bool TTemplate< Child, Parent, N >::Render(Parent* pParent)
{
	Child* pPoint = NULL;
	for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++ ) 
	{
		pPoint = (Child *)(*itor).second;
		if( pPoint )
		{
			pPoint->Render(pParent);			
		}
	}	
	return true;
}
}