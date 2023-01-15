#include "raylib.h"
#include "ScrEnding.h"
//#include "../GameManager.h"

ScrEnding::ScrEnding()
{

}
// Title Screen Initialization logic
void ScrEnding::Init(void)
{

}

// Title Screen Update logic
void ScrEnding::Update(void)
{
    GameManager* gm = &GameManager::GetGameManager();
    if (IsKeyPressed(KEY_ENTER))
    {
        gm->ChangeToScreen(GameScreen::TITLE);  // GAMEPLAY
    }

    if (IsKeyPressed(KEY_O))
    {
        gm->ChangeToScreen(GameScreen::OPTIONS);  // OPTIONS
    }
}

// Title Screen Draw logic
void ScrEnding::Draw(void)
{
    GameManager* gm = &GameManager::GetGameManager();
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    const char* line1;
    if (gm->GetEatenDots() >= 218)
    {
        line1 = "HAS GANADO :)";
        if (!playMusic)
        {
            gm->GetAudioMngr().PlaySoundEffect(SoundType::Victory);
            playMusic = true;  
        }
    }
    else if (gm->GetLives() <= 0)
    {
        line1 = "HAS PERDIDO :(";
        if (!playMusic)
        {
        gm->GetAudioMngr().PlaySoundEffect(SoundType::GameOver);
        playMusic = true;
        }
    }
    else 
    {
        line1 = "ESTO ES UN BUG :(";
    }
    
    const char* line2 = "Presiona Enter para Jugar";
    const char* line3 = "Presiona 'O' para Instrucciones";

    DrawText(line1, (GetScreenWidth() / 2.f) - (MeasureText(line1, 40) / 2.), 350, 40, WHITE);
    DrawText(line2, (GetScreenWidth() / 2.f) - (MeasureText(line2, 25) / 2.), 600, 25, WHITE);
    DrawText(line3, (GetScreenWidth() / 2.f) - (MeasureText(line3, 25) / 2.), 630, 25, WHITE);
}

void ScrEnding::Unload(void)
{

}

