#include "AudioManager.h"

AudioManager* AudioManager::s_pInstance = nullptr;

void AudioManager::playSound(string name)
{
	/*fstream fp;
	fp.open(name, ios::in);
	wstring tmp = std::wstring(name.begin(), name.end());*/
	/*mciSendString((LPCWSTR)"open ding_2.wav alias ding_2.wav", NULL, 0, 0);
	mciSendString((LPCWSTR)"play ding_2.wav", NULL, 0, 0);
}*/

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

AudioManager::AudioManager(const AudioManager&)
{
}
