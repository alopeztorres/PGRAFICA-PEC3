#include "raylib.h"
#include "ScrTitle.h"
//#include "../GameManager.h"


//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------


ScrTitle::ScrTitle()
{

}
// Title Screen Initialization logic
void ScrTitle::Init(void)
{
    texture = &GameManager::GetGameManager().GetTextMngr().GetTexture(TextureType::PacmanLogo);
    position = Vector2{ GetScreenWidth() / 2 - (float)texture->width / 2, 200.0f };
}

// Title Screen Update logic
void ScrTitle::Update(void)
{
    GameManager* gm = &GameManager::GetGameManager();
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        gm->ChangeToScreen(GameScreen::GAMEPLAY);  // GAMEPLAY
        gm->GameSetup();  // GAMEPLAY
    }

    if (IsKeyPressed(KEY_O))
    {
        gm->ChangeToScreen(GameScreen::OPTIONS);  // OPTIONS
    }
    gm->GetAudioMngr().PlayIntroMusic(true);

    if (IsSoundPlaying(gm->GetAudioMngr().GameOver))
    {
        StopSound(gm->GetAudioMngr().GameOver);
    }    
    if (IsSoundPlaying(gm->GetAudioMngr().Victory))
    {
        StopSound(gm->GetAudioMngr().Victory);
    }
}

// Title Screen Draw logic
void ScrTitle::Draw(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    GameManager& GameInst = GameManager::GetGameManager();
    DrawTextureRec(*texture, { 0.f,0.f,(float)texture->width, (float)texture->height }, position, WHITE);
    const char* line1 = "por Andres Lopez T.";
    const char* line2 = "Presiona Enter para Jugar";
    const char* line3 = "Presiona 'O' para Instrucciones";

    DrawText(line1, (GetScreenWidth() / 2.f) - (MeasureText(line1, 20) / 2.), 500, 20, WHITE);
    DrawText(line2, (GetScreenWidth() / 2.f) - (MeasureText(line2, 25) / 2.), 600, 25, WHITE);
    DrawText(line3, (GetScreenWidth() / 2.f) - (MeasureText(line3, 25) / 2.), 630, 25, WHITE);
}

void ScrTitle::Unload(void)
{

 }

