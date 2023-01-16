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
    if (gm->currentLevel >= 4)
    {
        gm->ChangeToScreen(GameScreen::ENDING);  // GAMEPLAY
    }
}

// Title Screen Update logic
void ScrLoading::Update(void)
{
    framesCounter++;

    if (!loading)
    {
        loading = true;
        gm->LoadLevel(gm->currentLevel);
    }

    if (framesCounter > 180)
    {
        framesCounter = 0;
        gm->ChangeToScreen(GameScreen::GAMEPLAY);  // GAMEPLAY
    }
}

// Title Screen Draw logic
void ScrLoading::Draw(void)
{
    const char* line = "Cargando el Nivel";
    DrawText(line, (GetScreenWidth() / 2.f) - (MeasureText(line, 40) / 2.), 350, 40, WHITE);

    
}

void ScrLoading::Unload(void)
{

}