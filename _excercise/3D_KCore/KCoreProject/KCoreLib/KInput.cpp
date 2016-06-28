#include "KInput.h"

bool   KInput::InitDirectInput()
{
	HRESULT hr = S_OK;
	if (FAILED(hr = DirectInput8Create(g_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pDI, NULL)))
	{
		return false;
	}
	if (FAILED(hr = m_pDI->CreateDevice(GUID_SysKeyboard,
		&m_pKeyDevice, NULL)))
	{
		return false;
	}
	// 장치별 반환 데이터 설정
	m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	// 장치별 독점 및 비독점 설정(협조레벨)
	if (FAILED(hr = m_pKeyDevice->SetCooperativeLevel(g_hWnd,
		DISCL_NONEXCLUSIVE |
		DISCL_FOREGROUND |
		DISCL_NOWINKEY)))
	{
		return false;
	}

	while (m_pKeyDevice->Acquire() == DIERR_INPUTLOST);


	if (FAILED(hr = m_pDI->CreateDevice(GUID_SysMouse,
		&m_pMouseDevice, NULL)))
	{
		return false;
	}
	m_pMouseDevice->SetDataFormat(&c_dfDIMouse);

	if (FAILED(hr = m_pMouseDevice->SetCooperativeLevel(g_hWnd,
		DISCL_NONEXCLUSIVE |
		DISCL_BACKGROUND )))
	{
		return true;
	}
	while (m_pMouseDevice->Acquire() == DIERR_INPUTLOST);
	return hr;
}
// KeyCheck(VK_LEFT)
// KeyCheck('0');
// KeyCheck('A');
// 논리합 : 두개의 비트중에 1개라도 참이면 결과는 참이된다.
// 논리곱 : 두개의 비트 모두가 참 일 경우만 결과는 참이된다.
// 배타적 논리합 : 두개의 비트를 비교하여 서로 다를 경우에 참이된다.
// 배타적 논리곱 : 둘다 참일 경우만 거짓이 된다.
// 부정 : 한개의 비트를 반대로 처리한다.( 참=>거짓, 거짓->참)
// 논리합, 논리곱, 배타적 논리합, 배타적 논리곱, 부정
//   or     and      xor           xand          not
//   |       &       ^             없음          !   => 비트연산자
BYTE KInput::KeyCheck(BYTE dwKey)
{
	// GetKeyState()		// 동기적
	// GetAsyncKeyState()	// 비동기적
	BYTE sKey;
#ifdef WIN_KEY_USE
	sKey = GetAsyncKeyState(dwKey);
#else
	sKey = m_KeyState[dwKey];
#endif
	// 0x8000 =  10000000 00000000
	if (sKey & 0x80)
	{
		if (m_KeyStateOld[dwKey] == KEY_FREE)
			m_KeyStateOld[dwKey] = KEY_PUSH;
		else
			m_KeyStateOld[dwKey] = KEY_HOLD;
	}
	else
	{
		if (m_KeyStateOld[dwKey] == KEY_PUSH ||
			m_KeyStateOld[dwKey] == KEY_HOLD  )
			m_KeyStateOld[dwKey] = KEY_UP;
		else
			m_KeyStateOld[dwKey] = KEY_FREE;
	}
	return m_KeyStateOld[dwKey];
}
	// 클래스 멤버 변수 초기화
bool		KInput::Init()
{
	ZeroMemory(m_KeyState, sizeof(BYTE) * 256);
	ZeroMemory(m_KeyStateOld, sizeof(BYTE) * 256);
	ZeroMemory(m_MouseState, sizeof(BYTE) * 3);
	ZeroMemory(m_BeforeMouseState, sizeof(BYTE) * 3);
#ifndef WIN_KEY_USE
	InitDirectInput();
#endif
	return true;
};
// 매 프레임에서 계산을 담당한다.
bool		KInput::Frame() 
{	
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);
#ifndef WIN_KEY_USE
	HRESULT hr;
	if (m_pMouseDevice == NULL || m_pKeyDevice == NULL) return false;

	if (FAILED(hr = m_pKeyDevice->GetDeviceState(KEYSTATECOUNT, m_KeyState)))
	{
		while (m_pKeyDevice->Acquire() == DIERR_INPUTLOST);
		return true;
	}

	if (FAILED(hr = m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_DIMouseState)))
	{
		while (m_pMouseDevice->Acquire() == DIERR_INPUTLOST);
		return true;
	}
	for (int iButton = 0; iButton < 3; iButton++)
	{
		m_MouseState[iButton] = m_DIMouseState.rgbButtons[iButton];
	}
#endif
	for (int iButton = 0; iButton < 3; iButton++)
	{
		if (m_BeforeMouseState[iButton] == KEY_PUSH )
		{
			if (m_MouseState[iButton] == KEY_PUSH)
			{
				m_MouseState[iButton] = KEY_HOLD;
			}
		}
		if (m_BeforeMouseState[iButton] == KEY_UP)
		{
			if (m_MouseState[iButton] == KEY_UP)
			{
				m_MouseState[iButton] = KEY_FREE;
			}
		}	
		m_BeforeMouseState[iButton] = m_MouseState[iButton];
	}
	return true;
};
// 매 프레임에서 드로우를 담당한다.
bool		KInput::Render() 
{
	ZeroMemory(m_csBuffer, sizeof(TCHAR)* MAX_PATH);
	m_strList.clear();
	
	std::wstring strData0;
	if (m_MouseState[0] == TRUE)
	{
		strData0 = L"m_MouseState[0] ";
		m_strList.push_back(strData0);
	}
	
	std::wstring strData1;
	if (m_MouseState[1] == TRUE)
	{
		strData1 = L"m_MouseState[1] ";
		m_strList.push_back(strData1);
	}
	
	std::wstring strData2;
	if (m_MouseState[2] == TRUE)
	{
		strData2 = L"m_MouseState[2] ";
		m_strList.push_back(strData2);
	}	
	return true;
};
// 클래스 멤버 변수 소멸을 담당한다.
bool		KInput::Release() 
{
	if(m_pKeyDevice)m_pKeyDevice->Unacquire();
	if(m_pMouseDevice)m_pMouseDevice->Unacquire();
	SAFE_RELEASE(m_pKeyDevice);
	SAFE_RELEASE(m_pMouseDevice);
	SAFE_RELEASE(m_pDI);
	return true;
};
void KInput::MsgEvent(MSG msg)
{	
#ifndef WIN_KEY_USE
	return;
#endif
	switch (msg.message)
	{
		case WM_LBUTTONDOWN:
		{
			m_MouseState[0] = KEY_PUSH;
		}break;
		case WM_LBUTTONUP:
		{
			m_MouseState[0] = KEY_UP;
		}break;
		case WM_RBUTTONDOWN:
		{
			m_MouseState[1] = KEY_PUSH;
		}break;
		case WM_RBUTTONUP:
		{
			m_MouseState[1] = KEY_UP;
		}break;
		case WM_MBUTTONDOWN:
		{
			m_MouseState[2] = KEY_PUSH;
		}break;
		case WM_MBUTTONUP:
		{
			m_MouseState[2] = KEY_UP;
		}break;
	}
};
KInput::KInput()
{
	m_pMouseDevice == NULL;
	m_pKeyDevice == NULL;
}


KInput::~KInput()
{
}
