//FMOD includes
#pragma once
#pragma comment(lib,"fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"
#include <vector>
#include<string>

class SoundManager
{

public:
	enum SoundsList
	{
		BACKGROUND_MUSIC_LEVEL_1,
		BACKGROUND_MUSIC_LEVEL_2,
		EXPLOSION_SOUND
	};

	static SoundManager& Instance();


	void PlaySoundEffect(SoundManager::SoundsList p_effect);
	void PlaySoundBG(SoundManager::SoundsList p_effect);
	void StopSound();
	void UpdateSound();
	void Init();



	

private:
	SoundManager();

	const static char* BACKGROUND_MUSIC_LVL_1;
	const static char* BACKGROUND_MUSIC_LVL_2;
	const static char* EXPLOSION;

	FMOD::System *FMODsys; //will point to the FMOD system
	FMOD_RESULT result;
	FMOD::Sound *sound;
	std::vector<FMOD::Sound*> sounds;
	FMOD::Channel *channel;
	FMOD::Channel *channel20;
};