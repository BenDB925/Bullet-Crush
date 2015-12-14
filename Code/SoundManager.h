//FMOD includes
#pragma once
#pragma comment(lib,"fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"
#include <vector>
#include<string>
#include "SFML\System\Vector2.hpp"

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


	void PlaySoundEffect3D(sf::Vector2f p_pos);
	void PlaySoundBG(SoundManager::SoundsList p_effect);

	void PlaySoundBGTest();

	void StopSound();
	void UpdateSound(sf::Vector2f p_pos, sf::Vector2f p_vel);
	void Init();

	bool Sound3Denabled;
	bool dopplerEnabaled;
	bool reverbEnabled;
	FMOD::Reverb *reverb;
	

private:
	SoundManager();

	const static char* BACKGROUND_MUSIC_LVL_1;
	const static char* BACKGROUND_MUSIC_LVL_2;
	const static char* EXPLOSION;
	float volume;
	FMOD::System *FMODsys; //will point to the FMOD system
	FMOD::System *FMODsys2;
	FMOD_RESULT result;
	FMOD::Sound *sound;
	std::vector<FMOD::Sound*> sounds;
	FMOD::Channel *channel;
	FMOD::Channel *channel20;
	FMOD_VECTOR sourcePos; 
};