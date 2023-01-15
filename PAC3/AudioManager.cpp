#include "AudioManager.h"



AudioManager::AudioManager()
{

}

void AudioManager::InitAudioFiles()
{
    InitAudioDevice();

    //Music
    IntroMusic = LoadMusicStream("PAC3Resources/Audio/Music/IntroTheme.mp3");	// Load Intro theme music
    Level1 = LoadMusicStream("PAC3Resources/Audio/Music/level1.mp3");
    Level2 = LoadMusicStream("PAC3Resources/Audio/Music/level2.mp3");
    Level3 = LoadMusicStream("PAC3Resources/Audio/Music/level3.mp3");
    End = LoadMusicStream("PAC3Resources/Audio/Music/GameOverTheme.mp3");
    
    //Sounds
    Dead = LoadSound("PAC3Resources/Audio/Sounds/death.mp3");
    Door = LoadSound("PAC3Resources/Audio/Sounds/door.mp3");
    Collectable = LoadSound("PAC3Resources/Audio/Sounds/pickup.mp3");


    SetMusicVolume(IntroMusic, 1.0f);
    PlayIntroMusic(true);

    //SetMusicVolume(Level1, 1.0f);
    //PlayLevel1Music(true);


}

void AudioManager::PlayIntroMusic(bool activate)
{
    if (activate)
        PlayMusicStream(IntroMusic);
    else
        StopMusicStream(IntroMusic);
}

void AudioManager::UpdateIntroMusic()
{
    UpdateMusicStream(IntroMusic);
}

void AudioManager::PlayEndMusic(bool activate)
{
    if (activate)
        PlayMusicStream(End);
    else
        StopMusicStream(End);
}

void AudioManager::UpdateEndMusic()
{
    UpdateMusicStream(End);
}

void AudioManager::PlayLevel1Music(bool activate)
{
    if (activate)
        PlayMusicStream(Level1);
    else
        StopMusicStream(Level1);
}

void AudioManager::UpdateLevel1Music()
{
    UpdateMusicStream(Level1);
}

void AudioManager::PlayLevel2Music(bool activate)
{
    if (activate)
        PlayMusicStream(Level2);
    else
        StopMusicStream(Level2);
}

void AudioManager::UpdateLevel2Music()
{
    UpdateMusicStream(Level2);
}

void AudioManager::PlayLevel3Music(bool activate)
{
    if (activate)
        PlayMusicStream(Level3);
    else
        StopMusicStream(Level3);
}

void AudioManager::UpdateLevel3Music()
{
    UpdateMusicStream(Level3);
}


void AudioManager::PlaySoundEffect(SoundType sound)
{
    switch (sound)
    {
    case SoundType::Dead:
        PlaySound(Dead);
        break;
    case SoundType::Door:
        PlaySound(Door);
        break;
    case SoundType::Collectable:
        PlaySound(Collectable);
        break;
    default:
        break;
    }
}

void AudioManager::UnloadAudioFiles()
{

    UnloadSound(Dead);
    UnloadSound(Collectable);
    UnloadSound(Door);


    //CloseAudio
    CloseAudioDevice();

}