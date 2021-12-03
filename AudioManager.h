#pragma once

#include <iostream>

using namespace std;


class AudioManager
{
public:
	static AudioManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new AudioManager();
			return s_pInstance;
		}
		return s_pInstance;
	}


	void playSound(string name);

private:
	static AudioManager* s_pInstance;



	AudioManager();
	~AudioManager();

	AudioManager(const AudioManager&);
};

