#include "stdafx.h"
#include "SoundManager.h"


const char * SoundManager::BACKGROUND_MUSIC_LVL_1 = "stage1.mp3";
const char * SoundManager::BACKGROUND_MUSIC_LVL_2 = "stage1.mp3";
const char * SoundManager::EXPLOSION = "exp.wav";


SoundManager::SoundManager()
{
	sounds = std::vector<FMOD::Sound *>();
	result = FMOD::System_Create(&FMODsys);         // Create the main system object.
	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
}

void SoundManager::PlaySoundEffect(SoundManager::SoundsList p_effect)
{
	//FMODsys->playSound(FMOD_CHANNEL_FREE, sound, false, NULL);

	FMODsys->playSound(FMOD_CHANNEL_REUSE, sounds.at(1), false, &channel20);
}
void SoundManager::PlaySoundBG(SoundManager::SoundsList p_effect)
{
	if (p_effect == SoundManager::SoundsList::BACKGROUND_MUSIC_LEVEL_1)
		FMODsys->playSound(FMOD_CHANNEL_FREE, sounds.at(0), false, &channel);
}

void SoundManager::StopSound()
{

}

void SoundManager::UpdateSound()
{

}

void SoundManager::Init()
{
	FMODsys->createSound(BACKGROUND_MUSIC_LVL_1, FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	FMODsys->createSound(EXPLOSION, FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);



}

SoundManager& SoundManager::Instance()
{
	static SoundManager instance;
	return instance;
}


