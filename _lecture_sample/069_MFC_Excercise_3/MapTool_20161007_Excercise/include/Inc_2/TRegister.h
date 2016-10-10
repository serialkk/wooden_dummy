#pragma once
#include "TBasisStd.h"
#include <stdio.h> 
#include <stdarg.h>

class TRegister: public TSingleton < TRegister >
{
	private:
		friend class TSingleton<TRegister>;
	public:
		TCHAR			  m_szDefaultResPath[MAX_PATH];		
		DWORD             m_dwCreationWidth;   // Width used to create window
		DWORD             m_dwCreationHeight;  // Height used to create window
		RECT              m_rcWindowBounds;    // Saved window bounds for mode switches
		RECT              m_rcWindowClient;    // Saved client area size for mode switches

		VOID ReadSettings();
		VOID WriteSettings();
		VOID WritePathSettings( TCHAR* strPath );
		 bool			Init();
		 bool			Frame();
		 bool			Render();
		 bool			Release();	
		 bool			ResetResource();
		 bool			ResetDevice();
public:
	//-----------------------------------------------------------------------------
	// Name: Read*RegKey() and Write*RegKey()
	// Desc: Helper functions to read/write a string registry key 
	//-----------------------------------------------------------------------------
	HRESULT WriteStringRegKey( HKEY hKey, TCHAR* strRegName, TCHAR* strValue );
	HRESULT WriteIntRegKey( HKEY hKey, TCHAR* strRegName, DWORD dwValue );
	HRESULT WriteGuidRegKey( HKEY hKey, TCHAR* strRegName, GUID guidValue );
	HRESULT WriteBoolRegKey( HKEY hKey, TCHAR* strRegName, BOOL bValue );

	HRESULT ReadStringRegKeyCch( HKEY hKey, TCHAR* strRegName, TCHAR* strDest, DWORD cchDest, TCHAR* strDefault );
	HRESULT ReadStringRegKeyCb( HKEY hKey, TCHAR* strRegName, TCHAR* strDest, DWORD cbDest, TCHAR* strDefault );
	HRESULT ReadIntRegKey( HKEY hKey, TCHAR* strRegName, DWORD* pdwValue, DWORD dwDefault );
	HRESULT ReadGuidRegKey( HKEY hKey, TCHAR* strRegName, GUID* pGuidValue, GUID& guidDefault );
	HRESULT ReadBoolRegKey( HKEY hKey, TCHAR* strRegName, BOOL* pbValue, BOOL bDefault );

	//-----------------------------------------------------------------------------
	// UNICODE support for converting between CHAR, TCHAR, and WCHAR strings
	//-----------------------------------------------------------------------------
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
	TRegister(void);
	virtual ~TRegister(void);
};
#define I_Register TRegister::GetInstance()