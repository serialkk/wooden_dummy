#pragma once
#include "TBase.h"
class TTimer : public TBase
{
public:
	int		 m_iFPS; // �ʴ� ������ ī����
	float	 m_fSecondPerFrame;// �ð��� ����ȭ
	float	 m_fAccumulation; // �������Ŀ� ����ð�.
public:
	TCHAR    m_csBuffer[MAX_PATH];
	DWORD	 m_dwBeforeTick;
	float    m_fFrameTime;
	DWORD	 m_dwFrameCounter;
public:
	bool     Init(); // �ʱ�ȭ
	bool     Frame();// ���
	bool     Render();// ��ο�
	bool     Release();// ����, �Ҹ�
public:
	TTimer();
	virtual ~TTimer();
};

