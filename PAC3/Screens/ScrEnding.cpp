#include "raylib.h"
#include "ScrEnding.h"
#include "../GameManager.h"

ScrEnding::ScrEnding()
{

}
// Title Screen Initialization logic
void ScrEnding::Init(void)
{
    gm = &GameManager::GetGameManager();
}

// Title Screen Update logic
void ScrEnding::Update(void)
{
    gm->GetAudioMngr().PlayEndMusic(true);
    gm->GetAudioMngr().UpdateEndMusic();
    gm->GetAudioMngr().PlayIntroMusic(false);
    gm->GetAudioMngr().PlayLevel1Music(false);
    gm->GetAudioMngr().PlayLevel2Music(false);
    gm->GetAudioMngr().PlayLevel3Music(false);

    if (gm->currentLevel < 4)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            gm->ChangeToScreen(GameScreen::LOADING);  // GAMEPLAY
            gm->UnloadObjects();
            gm->scLoading.Reload();
        }
        if (IsKeyPressed(KEY_O))
        {
            gm->ChangeToScreen(GameScreen::TITLE);  // OPTIONS
            gm->currentLevel = 1;
        }
    }
    else {
        if (IsKeyPressed(KEY_ENTER))
        {
            gm->ChangeToScreen(GameScreen::TITLE);  // TITLE SCREEN
            gm->currentLevel = 1;

        }

        if (IsKeyPressed(KEY_O))
        {
            gm->ChangeToScreen(GameScreen::OPTIONS);  // OPTIONS
            gm->currentLevel = 1;
        }
    }


}

// Title Screen Draw logic
void ScrEnding::Draw(void)
{
    //GameManager* gm = &GameManager::GetGameManager();
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    
    if (gm->currentLevel < 4)
    {
        const char* line1 = "GAME OVER :(";
        const char* line2 = "Presiona Enter para continuar";
        const char* line3 = "Presiona 'O' para volver al Menu Principal";


        DrawText(line1, (GetScreenWidth() / 2.f) - (MeasureText(line1, 40) / 2.), 350, 40, WHITE);
        DrawText(line2, (GetScreenWidth() / 2.f) - (MeasureText(line2, 25) / 2.), 600, 25, WHITE);
        DrawText(line3, (GetScreenWidth() / 2.f) - (MeasureText(line3, 25) / 2.), 630, 25, WHITE);
    }
    else 
    {
        const char* line1 = "LO HAS LOGRADO :)";
        const char* line2 = "Presiona Enter para volver al Menu Principal";
        const char* line3 = "Presiona 'O' para ver las instrucciones";


        DrawText(line1, (GetScreenWidth() / 2.f) - (MeasureText(line1, 40) / 2.), 350, 40, WHITE);
        DrawText(line2, (GetScreenWidth() / 2.f) - (MeasureText(line2, 25) / 2.), 600, 25, WHITE);
        DrawText(line3, (GetScreenWidth() / 2.f) - (MeasureText(line3, 25) / 2.), 630, 25, WHITE);
    }
}

void ScrEnding::Unload(void)
{

}

