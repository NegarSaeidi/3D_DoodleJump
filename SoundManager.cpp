#include "SoundManager.h"
SoundManager* SoundManager::s_pInstance=nullptr;

bool SoundManager::playSound(std::string name)
{
	return PlaySound(TEXT("ding_2.wav"), NULL, SND_SYNC);
	
}

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}
