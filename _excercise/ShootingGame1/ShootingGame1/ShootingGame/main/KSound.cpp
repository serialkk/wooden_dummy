#include "KSound.h"
void   KSound::Volume(int iIndex, float fVolume, bool bUp)
{
	float fCurrentVolume;
	m_pChannel[iIndex]->getVolume(&fCurrentVolume);
	if (bUp) fCurrentVolume += fVolume;
	else      fCurrentVolume -= fVolume;
	m_pChannel[iIndex]->setVolume(fCurrentVolume);

}
bool KSound::Init()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	return true;
};
int   KSound::Load(char* pLoadName)
{
	m_pSystem->createSound(pLoadName, 
		FMOD_HARDWARE, 0, &m_pSound[m_iSoundList++]);
	return m_iSoundList-1;
}
void  KSound::Play(int iIndex, bool bPlay )
{
	bool playing = false;
	if (bPlay == false)
	{
		if (m_pChannel[iIndex] != NULL)
		{
			m_pChannel[iIndex]->isPlaying(&playing);
		}
	}
	if (playing == false)
	{
		m_pSystem->playSound(FMOD_CHANNEL_FREE,
			m_pSound[iIndex], false, &m_pChannel[iIndex]);
	}
}
void  KSound::Release()
{
	for (int iSound = 0; iSound < g_iMaxSound; iSound++)
	{
		m_pSound[iSound]->release();
	}
	m_pSystem->close();
	m_pSystem->release();
}
KSound::KSound()
{
	m_iSoundList = 0;
}


KSound::~KSound()
{
}
