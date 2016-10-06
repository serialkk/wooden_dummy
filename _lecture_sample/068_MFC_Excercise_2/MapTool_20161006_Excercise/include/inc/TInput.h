#pragma once
#include "TBasisStd.h"
#include <dinput.h>

#define SAMPLE_BUFFER_SIZE 16 


namespace TBASIS_BASE { 

class TInput : public TSingleton < TInput >
{
private:
	friend class TSingleton<TInput>;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	bool		ResetDevice();
	bool		ResetResource(){return true;};
public:
	LPDIRECTINPUT8			m_pDi;
	LPDIRECTINPUTDEVICE8	m_pDidevKey;
	LPDIRECTINPUTDEVICE8	m_pDidevMouse;
	DIDEVICEOBJECTDATA		m_didod[ SAMPLE_BUFFER_SIZE ];

	BYTE					m_KeyState[256];
	BYTE					m_KeyBeforeState[256];
	DIMOUSESTATE			m_MouseState;
	DIMOUSESTATE			m_MouseBeforeState;
	DWORD					m_dwElements;
	HWND					m_hWnd;
	DWORD					m_dwImmediate;
public:
	bool		InitDirectInput(HINSTANCE, HWND, bool, bool);
	bool		KeyProcess();
	bool		MouseProcess();
	void		DeviceAcquire();
	void		DeviceUnacquire();	
	bool		OneKeyDown( DWORD dwKey );
	bool		IsKeyDown( DWORD dwKey );
	bool		IsKeyUP( DWORD dwKey );
	bool		PostProcess();
public:
	TInput(void);
	virtual ~TInput(void);
};
#define I_Input TInput::GetInstance()
}
 
