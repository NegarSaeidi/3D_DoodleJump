#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

#pragma comment(lib, "winmm.lib")
 class SoundManager
{
public:
	static SoundManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new SoundManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	//bool load(std::string fileName, std::string id, sound_type type);
	bool playSound(std::string name);
	
private:
	static SoundManager* s_pInstance;

	

	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&);
};
