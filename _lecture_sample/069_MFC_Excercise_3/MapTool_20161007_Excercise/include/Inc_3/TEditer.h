#pragma once
#include "TBasisStd.h"

class TEditer
{
public:
	bool						m_bReload;
	bool						Create( TCHAR_STRING ShaderPath, HWND hWnd );
	bool						IsReload();

protected:	
	HWND						m_hWnd;
	PROCESS_INFORMATION			m_NotePad_PI;
	TCHAR_STRING				m_strFileName;
	_WIN32_FILE_ATTRIBUTE_DATA	m_fileAttData;
	//--------------------------------------------------------------------------------------
	// Update
	//--------------------------------------------------------------------------------------	
	bool						Update();
	BOOL						SafeTerminateProcess(HANDLE hProcess, UINT uExitCode);

public:	
	int							MsgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

public:
	bool	Frame();
	bool	Release();
	bool	Init();
public:
	TEditer(void);
	virtual ~TEditer(void);
};
