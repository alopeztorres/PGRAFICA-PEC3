#include "raylib.h"
#include "ScrLoading.h"
#include "../GameManager.h"

ScrLoading::ScrLoading()
{

}
// Title Screen Initialization logic
void ScrLoading::Init(void)
{
    gm = &GameManager::GetGameManager();
    loading = true;
}

void ScrLoading::Reload()
{
    framesCounter = 0;
    loading = false;
}

// Title Screen Update logic
void ScrLoading::Update(void)
{
    framesCounter++;

    if (framesCounter > 180)
    {
        framesCounter = 0;
        //gm->ChangeToScreen(GameScreen::TITLE);
        gm->ChangeToScreen(GameScreen::GAMEPLAY);  // GAMEPLAY
    }

    if (!loading)
    {
        loading = true;
        gm->LoadLevel(gm->currentLevel);
    }
    //GameManager* gm = &GameManager::GetGameManager();
    //if (IsKeyPressed(KEY_ENTER))
    //{
      //  gm->ChangeToScreen(GameScreen::GAMEPLAY);  // GAMEPLAY
        //gm->LoadLevel(gm->currentLevel);
    //}
    
    /*
    if (IsKeyPressed(KEY_O))
    {
        gm->ChangeToScreen(GameScreen::OPTIONS);  // OPTIONS
    }
    */
}

// Title Screen Draw logic
void ScrLoading::Draw(void)
{
    //GameManager* gm = &GameManager::GetGameManager();

    /*
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
    */
    const char* line2 = "Cargando el Nivel";

    //DrawText(line1, (GetScreenWidth() / 2.f) - (MeasureText(line1, 40) / 2.), 350, 40, WHITE);
    DrawText(line2, (GetScreenWidth() / 2.f) - (MeasureText(line2, 40) / 2.), 350, 40, WHITE);

    
}

void ScrLoading::Unload(void)
{

}