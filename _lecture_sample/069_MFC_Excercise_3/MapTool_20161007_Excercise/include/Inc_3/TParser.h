#pragma once
#include "TBasis.h"

enum SET_DATA_TYPES
{
	// Gameplay semantics
	NULL_DATA	= 0,
	BOOL_DATA,
	INT_DATA,
	FLOAT_DATA,
	STRING_DATA,
	VERTEX_DATA,
	VECTOR_DATA,
	INDEX_DATA,
	FACE_DATA,
	MATRIX_DATA,
};

class TParser
{
public:

public:
	FILE*	m_pStream;
public:
	TCHAR	m_pBuffer[256];
	TCHAR	m_pString[256];
public:
	BOOL	ComparisonData		(	TCHAR* pDestString, TCHAR* pSrcString = NULL );		
	bool	ErrorCloseStream	(	TCHAR* pMsg		);		
	BOOL	OpenStream			(	const TCHAR* pFileName );
	BOOL    CloseStream()		{	fclose( m_pStream); return TRUE; };

	
	BOOL	GetData( VOID* pData, INT DataType);
	// 전체파일에서 해당 문자열을 찾을때 까지 검색하고 파일포인터를 다음라인으로 옮긴다.
	BOOL	GetDataFromFileLoop	(	TCHAR* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA);
	// 다음라인을 대상으로 문장열을 찾고 다음라인으로 파일포인터를 옮긴다.
	BOOL	GetDataFromFileNext	(	TCHAR* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA);
	// 원하는 문자열을 찾고 찾은 문자열 시작위치로 옮긴다
	BOOL	GetDataFromFileString	(	TCHAR* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA  );
	// 다음라인을 대상으로 해당문자열을 찾고 검색을 실폐하면 이전 라인으로 파일포인터를 옮긴다.
	BOOL	GetDataFromFile		(	TCHAR* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA);
	BOOL    GetNodeName			(   TCHAR* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA);

public:
	//-----------------------------------------------------------------------------
	// UNICODE support for converting between CHAR, TCHAR, and WCHAR strings
	//-----------------------------------------------------------------------------
	void	ConvertString( TCHAR_STRING& szReturn, TCHAR* szSource )
	{
		CHAR strDest[256] = {0,};
		WCHAR strConvert[256] = _T("");
		wcstombs( strDest, szSource, 256 );		
		ConvertAnsiStringToWideCch( strConvert, strDest, 256 );
		szReturn = strConvert;
	}
	HRESULT ConvertAnsiStringToWideCch( WCHAR* wstrDestination, const CHAR* strSource, int cchDestChar );
	HRESULT ConvertWideStringToAnsiCch( CHAR* strDestination, const WCHAR* wstrSource, int cchDestChar );
	HRESULT ConvertGenericStringToAnsiCch( CHAR* strDestination, const TCHAR* tstrSource, int cchDestChar );
	HRESULT ConvertGenericStringToWideCch( WCHAR* wstrDestination, const TCHAR* tstrSource, int cchDestChar );
	HRESULT ConvertAnsiStringToGenericCch( TCHAR* tstrDestination, const CHAR* strSource, int cchDestChar );
	HRESULT ConvertWideStringToGenericCch( TCHAR* tstrDestination, const WCHAR* wstrSource, int cchDestChar );
	HRESULT ConvertAnsiStringToWideCb( WCHAR* wstrDestination, const CHAR* strSource, int cbDestChar );
	HRESULT ConvertWideStringToAnsiCb( CHAR* strDestination, const WCHAR* wstrSource, int cbDestChar );
	HRESULT ConvertGenericStringToAnsiCb( CHAR* strDestination, const TCHAR* tstrSource, int cbDestChar );
	HRESULT ConvertGenericStringToWideCb( WCHAR* wstrDestination, const TCHAR* tstrSource, int cbDestChar );
	HRESULT ConvertAnsiStringToGenericCb( TCHAR* tstrDestination, const CHAR* strSource, int cbDestChar );
	HRESULT ConvertWideStringToGenericCb( TCHAR* tstrDestination, const WCHAR* wstrSource, int cbDestChar );
	HRESULT DXUtil_ConvertWideStringToAnsiCch( CHAR* strDestination, const WCHAR* wstrSource, 		int cchDestChar );
	//-----------------------------------------------------------------------------
	// GUID to String converting 
	//-----------------------------------------------------------------------------
	HRESULT ConvertGUIDToStringCch( const GUID* pGuidSrc, TCHAR* strDest, int cchDestChar );
	HRESULT ConvertGUIDToStringCb( const GUID* pGuidSrc, TCHAR* strDest, int cbDestChar );
	HRESULT ConvertStringToGUID( const TCHAR* strIn, GUID* pGuidOut );
public:
	TParser(void);
	virtual ~TParser(void);
};
