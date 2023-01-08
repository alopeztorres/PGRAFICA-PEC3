#include "TexturesManager.h"



TexturesManager::TexturesManager()
{

}



void TexturesManager::InitTexturesFiles()
{
    // Menu
    textLogo = LoadTexture("PacmanResources/Menu/Logo.png");
    textPacmanLogo = LoadTexture("PacmanResources/Menu/PacMan_MainLogo.png");

    //Gameplay
    textPacman = LoadTexture("PacmanResources/Game/PacMan.png");
    textGhost = LoadTexture("PacmanResources/Game/Enemies.png");
    textIconLifes = LoadTexture("PacmanResources/Game/IconLifes.png");
    textPacmanDead = LoadTexture("PacmanResources/Game/PacManDead.png");
    textTiles = LoadTexture("PacmanResources/TileMap/PacManTileset.png");
}

void TexturesManager::UnloadTexturesFiles()
{
    UnloadTexture(textLogo);
    UnloadTexture(textPacman);
    UnloadTexture(textIconLifes);
    UnloadTexture(textPacmanDead);
    UnloadTexture(textGhost);
    UnloadTexture(textTiles);
}

Texture2D& TexturesManager::GetTexture(TextureType texturetype)
{
    switch (texturetype)
    {
    case TextureType::Logo:
        return textLogo;
        break;
    case TextureType::PacmanLogo:
        return textPacmanLogo;
        break;
    case TextureType::IconLifes:
        return textIconLifes;
        break;
    case TextureType::Pacman:
        return textPacman;
        break;
    case TextureType::Dead:
        return textPacmanDead;
        break;
    case TextureType::Ghost:
        return textGhost;
        break;
    case TextureType::Tiles:
        return textTiles;
        break;
    default:
        return textLogo;
        break;
    }
}

