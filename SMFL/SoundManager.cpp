#include "stdafx.h"
#include "SoundManager.h"
#include "SFML\System\Vector2.hpp"


const char * SoundManager::BACKGROUND_MUSIC_LVL_1 = "stage1.mp3";
const char * SoundManager::BACKGROUND_MUSIC_LVL_2 = "stage1.mp3";
const char * SoundManager::EXPLOSION = "exp.wav";


SoundManager::SoundManager()
{
	Sound3Denabled = false;
	sounds = std::vector<FMOD::Sound *>();
	result = FMOD::System_Create(&FMODsys);         // Create the main system object.
	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
	FMOD::System_Create(&FMODsys2);
	FMODsys2->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
}

void SoundManager::PlaySoundEffect3D(sf::Vector2f p_pos)
{
	sourcePos = { p_pos.x, 0.0f, p_pos.y };

	float volume = 1.0f;
	FMODsys->playSound(FMOD_CHANNEL_REUSE, sounds.at(1), false, &channel20);
	channel20->setVolume(volume);
	channel20->set3DMinMaxDistance(250, 10000);
	channel20->set3DDopplerLevel(0);
}
void SoundManager::PlaySoundBG(SoundManager::SoundsList p_effect)
{
	if (p_effect == SoundManager::SoundsList::BACKGROUND_MUSIC_LEVEL_1)
		FMODsys2->playSound(FMOD_CHANNEL_FREE, sounds.at(0), false, &channel);
}

void SoundManager::StopSound()
{

}

void SoundManager::UpdateSound(sf::Vector2f p_pos, sf::Vector2f p_vel)
{

	if (Sound3Denabled)
	{
		FMOD_VECTOR  listenervel = { p_vel.x, 0.0f, p_vel.y };
		FMOD_VECTOR  listenerpos = { p_pos.x, 0.0f, p_pos.y };
		FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);
		channel20->set3DAttributes(&sourcePos, 0);
	}
	else
	{
		FMOD_VECTOR zero = { 0, 0, 0 };
		channel->set3DAttributes(&zero, 0);
		FMODsys->set3DListenerAttributes(0, &zero, &zero, 0, 0);
	}
	FMODsys->update();
	FMODsys2->update();
}

void SoundManager::Init()
{
	FMODsys2->createStream(BACKGROUND_MUSIC_LVL_1, FMOD_LOOP_NORMAL | FMOD_3D, 0, &sound);
	sounds.push_back(sound);

	/*
	FMOD::Reverb *reverb;
	FMODsys2->createReverb(&reverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_UNDERWATER;
	reverb->setProperties(&prop);
	FMOD_VECTOR pos = { 400, 0.0f,300 };
	float mindist = 100.0f;
	float maxdist = 150.0f;
	reverb->set3DAttributes(&pos, mindist, maxdist);
	reverb->setActive(true);
	*/


	FMODsys->createSound(EXPLOSION, FMOD_LOOP_OFF | FMOD_3D, 0, &sound);
	sounds.push_back(sound);
}

SoundManager& SoundManager::Instance()
{
	static SoundManager instance;
	return instance;
}


