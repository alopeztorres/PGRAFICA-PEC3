#include "raylib.h"
#include "ScrLogo.h"
//#include "../GameManager.h"

void ScrLogo::Unload() 
{
    UnloadTexture(*texture);
}

void ScrLogo::Init() {
    texture = &GameManager::GetGameManager().GetTextMngr().GetTexture(TextureType::Logo);
    position = Vector2{ GetScreenWidth()/2- (float)texture->width/2,GetScreenHeight()/2 - (float)texture->height/2 };
}

void ScrLogo::Draw() {
    DrawTextureRec(*texture, {0.f,0.f,(float)texture->width, (float)texture->height}, position, WHITE);
}

void ScrLogo::Update() {
    GameManager* gm = &GameManager::GetGameManager();
    framesCounter++;

    if (framesCounter > 180)
    {
        framesCounter = 0;
        gm->ChangeToScreen(GameScreen::TITLE);
    }
}

