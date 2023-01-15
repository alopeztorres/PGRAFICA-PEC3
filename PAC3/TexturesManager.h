#pragma once
#include "raylib.h"

enum class TextureType
{
	Logo = 0,
	MazeLogo
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
	Texture2D textLogo;
	Texture2D textMazeLogo;
};