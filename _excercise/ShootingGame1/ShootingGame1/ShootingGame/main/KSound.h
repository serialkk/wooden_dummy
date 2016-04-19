#pragma once
#include "KStd.h"
#include "fmod.hpp"
#include "fmod_errors.h"

#pragma comment( lib, "fmodex64_vc.lib")

using namespace FMOD;

const int g_iMaxSound = 3;
// c,  c++
class KSound
{
public:
	int				m_iSoundList;
	FMOD::System*   m_pSystem;
	FMOD::Sound*    m_pSound[g_iMaxSound];
	FMOD::Channel*    m_pChannel[g_iMaxSound];
public:
	bool	Init();
	int     Load(char* pLoadName);
	void	Play(int iIndex, bool bPlay);
	void    Stop(int iIndex)
	{
		m_pChannel[iIndex]->stop();
	}
	void    Paused(int iIndex)
	{
		bool paused;
		m_pChannel[iIndex]->getPaused(&paused);
		m_pChannel[iIndex]->setPaused(!paused);
	}
	void   Volume(int iIndex, float fVolume, bool bUp);
	void	Release();
public:
	KSound();
	virtual ~KSound();
};

