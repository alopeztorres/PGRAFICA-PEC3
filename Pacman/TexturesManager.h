#pragma once
#include "raylib.h"

enum class TextureType
{
	Logo = 0,
	PacmanLogo,
	Pacman,
	IconLifes,
	Dead,
	Ghost,
	Tiles
};

class TexturesManager
{
public:
	TexturesManager();

	void InitTexturesFiles();
	void UnloadTexturesFiles();

	//Functions For textures
	Texture2D& GetTexture(TextureType texture);

private:
	Texture2D textPacmanDead;
	Texture2D textIconLifes;
	Texture2D textLogo;
	Texture2D textPacman;
	Texture2D textPacmanLogo;
	Texture2D textGhost;
	Texture2D textTiles;
};