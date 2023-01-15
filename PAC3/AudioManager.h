#pragma once

#include "raylib.h"

enum class SoundType
{
	Dead,
	Door,
	Collectable
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
	void PlayLevel1Music(bool activate);
	void UpdateLevel1Music();
	void PlayLevel2Music(bool activate);
	void UpdateLevel2Music();
	void PlayLevel3Music(bool activate);
	void UpdateLevel3Music();
	void PlayEndMusic(bool activate);
	void UpdateEndMusic();

	void PlaySoundEffect(SoundType sound);


	Music IntroMusic;
	Music Level1;
	Music Level2;
	Music Level3;
	Music End;


	Sound Dead;
	Sound Door;
	Sound Collectable;
};
