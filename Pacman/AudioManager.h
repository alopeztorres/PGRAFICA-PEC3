#pragma once

#include "raylib.h"

enum class SoundType
{
	GameStart=0,
	Dead,
	Victory,
	Waka,
	EatGhost,
	GameOver,
	PowerPill,
};

class AudioManager
{
public:
	AudioManager();

	void InitAudioFiles();
	void UnloadAudioFiles();

	//Functons For music 
	void PlayIntroMusic(bool activate);
	void UpdateIntroMusic();
	void PlaySirenMusic(bool activate);
	void UpdateSirenMusic();

	void PlaySoundEffect(SoundType sound);


	Music IntroMusic;
	Music Siren;

	Sound GameOver;
	Sound PowerPill;
	Sound GameStart;
	Sound Dead;
	Sound Victory;
	Sound Waka;
	Sound EatGhost;
};
