#pragma once
#include "KWindow.h"
#include "KDxHelperEx.h"
#include "KTimer.h"
#include "KInput.h"
#include "KWrite.h"
using namespace DX;
class KCore : public KWindow
{
public:
	KTimer		m_Timer;
	KWrite		m_Font;
public:
	bool	GameRun();
	bool	GameInit();	
	bool	GameFrame();
	virtual bool	GameRender();
	bool    GameRelease();
	void	MsgEvent(MSG msg);

	virtual bool	DrawDebug();
	virtual bool    DrawDebug(TCHAR* pString, int iX, int iY);
	virtual bool	PreRender();
	virtual bool	PostRender();
public:
	////////// 가상 함수들 ///////////
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

