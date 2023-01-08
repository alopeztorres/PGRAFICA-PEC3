#pragma once
#include "raylib.h"

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
struct Tile
{
	int value;                  // Tile index value (in tileset)
	int collider;              // Tile collider (0 -> walkable)
	Color color;
};

struct Tilemap
{
	Tile* tiles;                // Tiles data
	Tile* objectTiles;
	int tileCountX;             // Tiles counter X
	int tileCountY;             // Tiles counter Y
	int tileSize;               // Tile size (XY)
	Vector2 position;           // Tilemap position in screen
};

enum GameScreen 
{ 
	LOGO = 0, 
	TITLE, 
	OPTIONS, 
	GAMEPLAY, 
	ENDING 
};
enum BehaviorState 
{ 
	CHASE = 0, 
	FRIGHTENED, 
	EATEN, 
	INHOME 
};

