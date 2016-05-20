#include "TSound.h"
void   TSound::Volume(int iIndex, float fVolume, bool bUp)
{
	float fCurrentVolume;
	m_pChannel[iIndex]->getVolume(&fCurrentVolume);
	if (bUp) fCurrentVolume += fVolume;
	else      fCurrentVolume -= fVolume;
	m_pChannel[iIndex]->setVolume(fCurrentVolume);

}
bool TSound::Init()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	return true;
};
bool TSound::Frame()
{
	//m_pChannel[0]->getLength()
	unsigned int total;
	unsigned int current;
	m_pSound[0]->getLength(&total, FMOD_TIMEUNIT_MS);
	m_pChannel[0]->getPosition(&current, FMOD_TIMEUNIT_MS);

	//TCHAR m_szBuffer[MAX_PATH] = { 0 };
	_stprintf_s(m_szBuffer, _T("[%02d:%02d:%02d] [%02d:%02d:%02d]"),
		current / 1000 / 60,
		current / 1000 % 60,
		current / 10 % 60,
		total / 1000 / 60, 
		total / 1000 % 60,
		total / 10 % 60 );
	return true;
}
int   TSound::Load(char* pLoadName)
{
	m_pSystem->createSound(pLoadName, 
		FMOD_HARDWARE, 0, &m_pSound[m_iSoundList++]);
	return m_iSoundList-1;
}
void  TSound::Play(int iIndex, bool bPlay )
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
void  TSound::Release()
{
	for (int iSound = 0; iSound < g_iMaxSound; iSound++)
	{
		m_pSound[iSound]->release();
	}
	m_pSystem->close();
	m_pSystem->release();
}
TSound::TSound()
{
	m_iSoundList = 0;
}


TSound::~TSound()
{
}
