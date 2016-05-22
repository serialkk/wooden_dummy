#include "KInput.h"
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
DWORD KInput::KeyCheck(DWORD dwKey)
{
	// GetKeyState()		// 동기적
	// GetAsyncKeyState()	// 비동기적
	SHORT sKey = GetAsyncKeyState(dwKey);
	// 0x8000 =  10000000 00000000
	if (sKey & 0x8000)
	{
		if (m_dwKeyState[dwKey] == KEY_FREE)
			m_dwKeyState[dwKey] = KEY_PUSH;
		else
			m_dwKeyState[dwKey] = KEY_HOLD;
	}
	else
	{
		if (m_dwKeyState[dwKey] == KEY_PUSH ||
			m_dwKeyState[dwKey] == KEY_HOLD  )
			m_dwKeyState[dwKey] = KEY_UP;
		else
			m_dwKeyState[dwKey] = KEY_FREE;
	}
	return m_dwKeyState[dwKey];
}
	// 클래스 멤버 변수 초기화
bool		KInput::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	ZeroMemory(m_dwMouseState, sizeof(DWORD) * 3);
	ZeroMemory(m_dwBeforeMouseState, sizeof(DWORD) * 3);
	return true;
};
// 매 프레임에서 계산을 담당한다.
bool		KInput::Frame() 
{	
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);

	for (int iButton = 0; iButton < 3; iButton++)
	{
		if (m_dwBeforeMouseState[iButton] == KEY_PUSH )
		{
			if (m_dwMouseState[iButton] == KEY_PUSH)
			{
				m_dwMouseState[iButton] = KEY_HOLD;
			}
		}
		if (m_dwBeforeMouseState[iButton] == KEY_UP)
		{
			if (m_dwMouseState[iButton] == KEY_UP)
			{
				m_dwMouseState[iButton] = KEY_FREE;
			}
		}	
		m_dwBeforeMouseState[iButton] = m_dwMouseState[iButton];
	}	
	return true;
};
// 매 프레임에서 드로우를 담당한다.
bool		KInput::Render() 
{
	ZeroMemory(m_csBuffer, sizeof(TCHAR)* MAX_PATH);
	m_strList.clear();
	/*for (int ikey = 0; ikey < 256; ikey++)
	{
		if (m_dwKeyState == KEY_FREE)
			strData += L"";
	}*/
	std::wstring strData0;
	if (m_dwMouseState[0] == TRUE)
	{
		strData0 = L"m_dwMouseState[0] ";
		m_strList.push_back(strData0);
	}
	
	std::wstring strData1;
	if (m_dwMouseState[1] == TRUE)
	{
		strData1 = L"m_dwMouseState[1] ";
		m_strList.push_back(strData1);
	}
	
	std::wstring strData2;
	if (m_dwMouseState[2] == TRUE)
	{
		strData2 = L"m_dwMouseState[2] ";
		m_strList.push_back(strData2);
	}	
	//_stprintf_s(m_csBuffer, L"%s\n", strData.c_str());
	//m_MovePt.x = 0;
	//m_MovePt.y = 0;
	return true;
};
// 클래스 멤버 변수 소멸을 담당한다.
bool		KInput::Release() 
{
	return true;
};
void KInput::MsgEvent(MSG msg)
{	
	switch (msg.message)
	{
		case WM_LBUTTONDOWN:
		{
			m_dwMouseState[0] = KEY_PUSH;
		}break;
		case WM_LBUTTONUP:
		{
			m_dwMouseState[0] = KEY_UP;
		}break;
		case WM_RBUTTONDOWN:
		{
			m_dwMouseState[1] = KEY_PUSH;
		}break;
		case WM_RBUTTONUP:
		{
			m_dwMouseState[1] = KEY_UP;
		}break;
		case WM_MBUTTONDOWN:
		{
			m_dwMouseState[2] = KEY_PUSH;
		}break;
		case WM_MBUTTONUP:
		{
			m_dwMouseState[2] = KEY_UP;
		}break;
	}
};
KInput::KInput()
{
}


KInput::~KInput()
{
}
