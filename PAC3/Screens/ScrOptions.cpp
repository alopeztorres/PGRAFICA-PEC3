#include "raylib.h"
#include "ScrOptions.h"
#include "../GameManager.h"


//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------


ScrOptions::ScrOptions()
{

}
// Title Screen Initialization logic
void ScrOptions::Init(void)
{
    gm = &GameManager::GetGameManager();
}

// Title Screen Update logic
void ScrOptions::Update(void)
{
    //GameManager* gm = &GameManager::GetGameManager();
    if (IsKeyPressed(KEY_O))
    {
        gm->ChangeToScreen(GameScreen::TITLE);  // OPTIONS
    }
}

// Title Screen Draw logic
void ScrOptions::Draw(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    const char* line1 = "Para mover a Pacman usa las teclas de Direccion A,D,W,S";
    const char* line2 = "Pacman tiene 3 vidas, cada punto comido obtienes 10 puntos";
    const char* line3 = "si comes los puntos grandes obtienes 50 puntos al puntaje";

    const char* line4 = "Para ganar Pacman debe comer todos los puntos";
    const char* line5 = "Tu pierdes si el fantasma Shadow te elimina 3 veces";

    DrawText(line1, (GetScreenWidth() / 2.f) - (MeasureText(line1, 28) / 2.), 300, 28, WHITE);
    DrawText(line2, (GetScreenWidth() / 2.f) - (MeasureText(line2, 28) / 2.), 330, 28, WHITE);
    DrawText(line3, (GetScreenWidth() / 2.f) - (MeasureText(line3, 28) / 2.), 360, 28, WHITE);
    DrawText(line4, (GetScreenWidth() / 2.f) - (MeasureText(line4, 28) / 2.), 390, 28, WHITE);
    DrawText(line5, (GetScreenWidth() / 2.f) - (MeasureText(line5, 28) / 2.), 420, 28, WHITE);

    const char* line7 = "Presiona 'O' para regresar al titulo.";

    DrawText(line7, (GetScreenWidth() / 2.f) - (MeasureText(line7, 25) / 2.), 510, 25, WHITE);
}

void ScrOptions::Unload(void)
{

}

