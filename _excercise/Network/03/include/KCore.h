#pragma once
#include "KWindow.h"
#include "KTimer.h"
#include "KInput.h"
class KCore : public KWindow
{
public:
	KTimer		m_Timer;
	KInput		m_Input;
	HDC			m_hScreenDC;   // ���� ����
	HBITMAP		m_hOldBitmap; // �ĸ������ �̹���

	HDC			m_hOffScreenDC;// �ĸ� ����
	HBITMAP		m_hOffScreenBitmap; // �ĸ������ �̹���	

	HBRUSH		m_hbrBack;
	HBRUSH		m_hbrOld;

	HFONT		m_fontDefault;
	HFONT		m_fontDefaultOld;
public:
	bool	GameRun();
	bool	GameInit();	
	bool	GameFrame();
	bool	GameRender();
	bool    GameRelease();
	void	MsgEvent(MSG msg);

	virtual bool	DrawDebug();
	virtual bool    DrawDebug(TCHAR* pString, int iX, int iY);
	virtual bool	PreRender();
	virtual bool	PostRender();
public:
	////////// ���� �Լ��� ///////////
	virtual bool		Init() { return true; }
	virtual bool		PreFrame() { return true; }	
	virtual bool		PostFrame() { return true; }	
	virtual bool		Frame() { return true; }
	virtual bool		Render() { return true; }
	virtual bool		Release() { return true; };
public:
	KCore();
	virtual ~KCore();
};

