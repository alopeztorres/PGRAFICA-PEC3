#include "TexturesManager.h"



TexturesManager::TexturesManager()
{

}



void TexturesManager::InitTexturesFiles()
{
    // Menu
    textLogo = LoadTexture("PAC3Resources/Menu/Logo.png");
    textMazeLogo = LoadTexture("PAC3Resources/Menu/GameLogo.png");
}

void TexturesManager::UnloadTexturesFiles()
{
    UnloadTexture(textLogo);
    UnloadTexture(textMazeLogo);
}

Texture2D& TexturesManager::GetTexture(TextureType texturetype)
{
    switch (texturetype)
    {
    case TextureType::Logo:
        return textLogo;
        break;
    case TextureType::MazeLogo:
        return textMazeLogo;
        break;
    default:
        return textLogo;
        break;
    }
}

