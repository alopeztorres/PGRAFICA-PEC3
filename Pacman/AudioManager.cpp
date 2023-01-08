#include "AudioManager.h"



AudioManager::AudioManager()
{

}

void AudioManager::InitAudioFiles()
{
    InitAudioDevice();

    //Music
    IntroMusic = LoadMusicStream("PacmanResources/Audio/Music/IntroTheme.mp3");	// Load Intro theme music
    Siren = LoadMusicStream("PacmanResources/Audio/Sounds/Siren.mp3");
    
    //Sounds
    GameStart = LoadSound("PacmanResources/Audio/Sounds/GameStart.mp3");
    Dead = LoadSound("PacmanResources/Audio/Sounds/Death.mp3");
    Victory = LoadSound("PacmanResources/Audio/Sounds/Victory.mp3");
    Waka = LoadSound("PacmanResources/Audio/Sounds/WakaWaka.mp3");
    PowerPill = LoadSound("PacmanResources/Audio/Sounds/EatingPowerPill.mp3");
    EatGhost = LoadSound("PacmanResources/Audio/Sounds/EatingGhost.mp3");
    GameOver = LoadSound("PacmanResources/Audio/Music/GameOverTheme.mp3");


    SetMusicVolume(IntroMusic, 1.0f);
    PlayIntroMusic(true);


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

void AudioManager::PlaySirenMusic(bool activate)
{
    if (activate)
        PlayMusicStream(Siren);
    else
        StopMusicStream(Siren);
}

void AudioManager::UpdateSirenMusic()
{
    UpdateMusicStream(Siren);
}


void AudioManager::PlaySoundEffect(SoundType sound)
{
    switch (sound)
    {
    case SoundType::GameStart:
        PlaySound(GameStart);
        break;
    case SoundType::Dead:
        PlaySound(Dead);
        break;
    case SoundType::Victory:
        PlaySound(Victory);
        break;
    case SoundType::Waka:
        PlaySound(Waka);
        break;
    case SoundType::EatGhost:
        PlaySound(EatGhost);
        break;
    case SoundType::GameOver:
        PlaySound(GameOver);
        break;
    case SoundType::PowerPill:
        PlaySound(PowerPill);
        break;
    default:
        break;
    }
}

void AudioManager::UnloadAudioFiles()
{
    UnloadSound(GameStart);
    UnloadSound(Dead);
    UnloadSound(Victory);
    UnloadSound(Waka);
    UnloadSound(EatGhost);
    UnloadSound(Waka);
    UnloadSound(GameOver);

    //CloseAudio
    CloseAudioDevice();

}