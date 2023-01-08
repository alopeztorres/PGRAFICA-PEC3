#pragma once

#include "raylib.h"

#include "Entidad.h"

#include "Screens/ScrLogo.h"  
#include "Screens/ScrTitle.h" 
#include "Screens/ScrOptions.h" 
#include "Screens/ScrEnding.h" 

#include "AudioManager.h"

#include <stdio.h>              // Standard input-output C library
#include <stdlib.h>             // Memory management functions: malloc(), free()
#include <string.h>             // String manipulation functions: strrchr(), strcmp()
#include <cmath>

using namespace std;

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static const int screenWidth = 1024;
static const int screenHeight = 864;
static const int offsetX = (screenWidth - 864) / 2;
static const int offsetY = (screenHeight - 736) / 2;


//Tilemap data loading and drawing
#define TILESET_TILES  30

static Rectangle pacmanTilesetRecs[TILESET_TILES] = {
	{ 0, 0, 32, 32 },   { 32, 0, 32, 32 },  { 64, 0, 32, 32 },         // 1, 2, 3
	{ 0, 32, 32, 32 },  { 32, 32, 32, 32 }, { 64, 32, 32, 32 },        // 4, 5, 6
	{ 0, 64, 32, 32 },  { 32, 64, 32, 32 }, { 64, 64, 32, 32 },        // 7, 8, 9

	{ 96, 0, 32, 32 },   { 128, 0, 32, 32 },  { 160, 0, 32, 32 },         // 10, 11, 12
	{ 96, 32, 32, 32 },  { 128, 32, 32, 32 }, { 160, 32, 32, 32 },        // 13, 14, 15
	{ 96, 64, 32, 32 },  { 128, 64, 32, 32 }, { 160, 64, 32, 32 },        // 16, 17, 18

	{ 192, 0, 32, 32 },                                                   // 19
	{ 192, 32, 32, 32 },                                                  // 20
	{ 192, 64, 32, 32 },                                                  // 21

	{ 224, 0, 32, 32 },   { 256, 0, 32, 32 },  { 288, 0, 32, 32 },         // 22, 23, 24
	{ 224, 32, 32, 32 },  { 256, 32, 32, 32 }, { 288, 32, 32, 32 },        // 25, 26, 27
	{ 224, 64, 32, 32 },  { 256, 64, 32, 32 }, { 288, 64, 32, 32 },        // 28, 29, 30
};



class GameManager
{
public:

	// Collision detection
#define PLAYER_COLLISION_PADDING    0      // Player padding to detect collision with ghost

	GameManager();

	void InitGame();            // Initialize game
	void UpdateFrame(int secondsPassed);      // Update game (one frame)
	void DrawFrame(void);                     // Draw game (one frame)
	void UnloadGame(void);

	TexturesManager& GetTextMngr() { return TextMngr; }
	AudioManager& GetAudioMngr() { return AudioMngr; }
	Font& GetFont() { return font; }
	int GetScore() { return score; }
	void SetScore(int newValue) { score = newValue; }
	bool GetDead() { return isDead; }
	void SetDead(bool resp) { isDead = resp; }
	bool GetStarted() { return started; }
	void SetStarted(bool resp) { started = resp; }
	int GetEatenDots() { return eatenDots; }
	void IncreaseScore(int newValue) { score += newValue; }
	int GetLives() { return lives; }
	void DecreaseLives(int newValue) { lives -= newValue; }
	void IncreaseEatenDots(int newValue) { eatenDots += newValue; }
	static GameManager& GetGameManager();
	static Tilemap LoadTilemap(const char* valuesMap, const char* collidersMap, const char* objectsMap);// Load tilemap data from file
	static void UnloadTilemap(Tilemap map);                   // Unload tilemap data
	static void DrawTilemap(Tilemap map, Texture2D tileset);  // Draw tilemap using tileset
	Tilemap* GetTilemap();
	BehaviorState GetGhostState();
	void SetGhostState(BehaviorState state);
	Entidad* GetGhost();
	Entidad* GetPlayer();
	void GameSetup();
	void ChangeToScreen(int screen);     // Change to screen, no transition effect

private:
	BehaviorState ghostState = CHASE;
	Entidad player;
	Entidad ghost;
	int framesCounter = 0;
	int score = 0;
	int eatenDots = 0;
	int lives = 3;
	bool started;
	bool isDead;

private:

	static GameManager* GameMngr;
	GameScreen currentScreen;
	Font font = { 0 };
	Texture2D texPlayer;
	Tilemap tilemap;
	Texture2D texTileset;
	Texture2D texLives;
	ScrLogo scLogo;
	ScrTitle scTitle;
	ScrOptions scOptions;
	ScrEnding scEnding;
	TexturesManager TextMngr = TexturesManager();
	AudioManager AudioMngr = AudioManager();
};