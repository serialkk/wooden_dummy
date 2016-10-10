#pragma once
#include "TParser.h"

class TLoadToken
{
public:
	TCHAR_STRING		m_szDirName;
	TCHAR_STRING		m_szName;
	HANDLE					m_hHandle;	
	CHAR*					m_pmbStaticMeshData;
	TCHAR*					m_pwcStaticMeshData;
	vector<TCHAR_STRING>	m_ListTokens; 
	TCHAR_STRING			m_pwcToken; 	
	TCHAR					m_pString[256];
	TCHAR*					m_pwcSearchData;
	TCHAR_STRING			m_pwcTokenData;
	INT						m_iData;	
	DWORD					m_dwTokenIndex;
	DWORD					m_dwMaxStringTable;
public:
	void			SetToken( TCHAR_STRING szToken ){ m_pwcToken = szToken; }
	bool			BeginToken();
	const TCHAR*	GetNextTokenString();
	const TCHAR*	GetCurrentTokenString();
	bool			LoadBuffer( const TCHAR* strFileName);
	INT				SearchTokenArray(INT NumObjType, TCHAR** pObjectType,  DWORD dwNextObjectIndex = 0);
	const TCHAR*	GetSearchString( PTCHAR szSearchData, bool bLoop = true  ) ;
	bool			DeleteBuffer();
public:
	template <typename OutputIterator>  
	void			Tokenize(const TCHAR_STRING& text, const TCHAR_STRING& delimiters, OutputIterator first); 
public:
	TLoadToken(void);
	~TLoadToken(void);
};