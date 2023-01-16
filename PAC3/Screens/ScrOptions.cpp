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

    const char* line1 = "Para mover a tu personaje usa las teclas de Direccion A,D,W,S";
    const char* line2 = "Para orbitar y mover la camara utiliza el mouse.";
    const char* line3 = "Hay una puerta que debes buscar en cada laberinto para avanzar.";
    const char* line4 = "Debes coleccionar todos los orbes para que puedas entrar a la puerta";
    const char* line5 = "que estan regados en cada uno de los laberintos";
    const char* line6 = "Evita la lava a toda costa, si la tocas mueres!!";
    const char* line7 = "Aunque si pierdes, puedes continuar en el mismo nivel :)";

    DrawText(line1, (GetScreenWidth() / 2.f) - (MeasureText(line1, 28) / 2.), 240, 28, WHITE);
    DrawText(line2, (GetScreenWidth() / 2.f) - (MeasureText(line2, 28) / 2.), 270, 28, WHITE);
    DrawText(line3, (GetScreenWidth() / 2.f) - (MeasureText(line3, 28) / 2.), 300, 28, WHITE);
    DrawText(line4, (GetScreenWidth() / 2.f) - (MeasureText(line4, 28) / 2.), 330, 28, WHITE);
    DrawText(line5, (GetScreenWidth() / 2.f) - (MeasureText(line5, 28) / 2.), 360, 28, WHITE);
    DrawText(line6, (GetScreenWidth() / 2.f) - (MeasureText(line6, 28) / 2.), 390, 28, WHITE);
    DrawText(line7, (GetScreenWidth() / 2.f) - (MeasureText(line7, 28) / 2.), 420, 28, WHITE);

    const char* line8 = "Presiona 'O' para regresar al titulo.";

    DrawText(line8, (GetScreenWidth() / 2.f) - (MeasureText(line8, 25) / 2.), 510, 25, WHITE);
}

void ScrOptions::Unload(void)
{

}

