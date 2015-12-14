#include "stdafx.h"
#include "SoundManager.h"
#include "SFML\System\Vector2.hpp"


const char * SoundManager::BACKGROUND_MUSIC_LVL_1 = "resources/stage1.mp3";
const char * SoundManager::BACKGROUND_MUSIC_LVL_2 = "resources/stage1.mp3";
const char * SoundManager::EXPLOSION = "resources/exp.wav";


SoundManager::SoundManager()
{
	reverbEnabled = false;
	dopplerEnabaled = false;
	Sound3Denabled = false;
	sounds = std::vector<FMOD::Sound *>();
	result = FMOD::System_Create(&FMODsys);         // Create the main system object.
	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
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
	{
		sourcePos = { 300, 0.0f, 400 };
		float volume = 1.0f;
		FMODsys->playSound(FMOD_CHANNEL_REUSE, sounds.at(0), false, &channel);
		channel->setVolume(volume);
		channel->set3DMinMaxDistance(250, 10000);

		FMODsys->createReverb(&reverb);
		FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_SEWERPIPE;
		reverb->setProperties(&prop);
		FMOD_VECTOR pos = { 300, 0.0f, 400 };
		float mindist = 150;
		float maxdist = 150;
		reverb->set3DAttributes(&pos, mindist, maxdist);
		reverb->setActive(false);

	}
}

void SoundManager::StopSound()
{

}

void SoundManager::UpdateSound(sf::Vector2f p_pos, sf::Vector2f p_vel)
{
	FMOD_VECTOR  listenerpos = { p_pos.x, 0.0f, p_pos.y };
	FMOD_VECTOR  listenervel = { 0.0f, 0.0f, 0.0f };

	if (Sound3Denabled)
	{
		if (dopplerEnabaled)
			listenervel = { p_vel.x, 0.0f, p_vel.y };

		FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);
		channel20->set3DAttributes(&sourcePos, 0);
	}
	else
	{
		FMOD_VECTOR zero = { 0, 0, 0 };
		channel20->set3DAttributes(&zero, 0);
		FMODsys->set3DListenerAttributes(0, &zero, &zero, 0, 0);
	}
	FMODsys->update();
}

void SoundManager::Init()
{
	FMODsys->createStream(BACKGROUND_MUSIC_LVL_1, FMOD_LOOP_NORMAL | FMOD_3D, 0, &sound);
	sounds.push_back(sound);


	FMODsys->createSound(EXPLOSION, FMOD_LOOP_OFF | FMOD_3D, 0, &sound);
	sounds.push_back(sound);
}

SoundManager& SoundManager::Instance()
{
	static SoundManager instance;
	return instance;
}


