#pragma once

#include "raylib.h"

#include "Screens/ScrLogo.h"  
#include "Screens/ScrTitle.h" 
#include "Screens/ScrOptions.h" 
#include "Screens/ScrLoading.h"  
#include "Screens/ScrEnding.h" 

#include "AudioManager.h"

#include <stdio.h>              // Standard input-output C library
#include <stdlib.h>             // Memory management functions: malloc(), free()
#include <string>             // String manipulation functions: strrchr(), strcmp()
#include <cmath>
#include <vector>

#include "GlobalDefines.h"

using namespace std;

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
const int screenWidth = 1020;
const int screenHeight = 800;

struct ObjDetails
{
	int modelType = 0;
	Vector3 position = Vector3{ 0,0,0 };
	bool collider = false;
	bool exit = false;
	bool collectable = false;
	bool hidden = false;
};



struct Prop
{
    Model model;
    Texture2D text;
    string name;
};




class GameManager
{
public:
	vector<Prop*> propList;
	vector<ObjDetails*> objList;
	ScrLoading scLoading;

	int currentLevel;
	int currentOrbs = 0;
	int orbsToCollect;

	GameManager();

	void InitGame();            // Initialize game
	void UpdateFrame(int secondsPassed);      // Update game (one frame)
	void DrawFrame(void);                     // Draw game (one frame)
	void UnloadGame(void);

	static GameManager& GetGameManager();
	TexturesManager& GetTextMngr() { return TextMngr; }
	AudioManager& GetAudioMngr() { return AudioMngr; }
	Font& GetFont() { return font; }

	void LoadLevel(int levelNumber);
	void UnloadProps();
	void UnloadObjects();
	void PlayLevelMusic();
	void AddObj(ObjDetails* props);
	void AddProp(char* modelLocation, char* textureLocation, std::string name);
	void SetOrbsToCollectOnLevel();
	void RenderProps();
	void ChangeToScreen(int screen);     // Change to screen, no transition effect
	Mesh GenMeshCubicmapV2(Image cubicmap, Vector3 cubeSize);

	
private:
	Camera3D camera = { 0 };
	Image imMap;
	Texture2D cubicmap;
	Mesh mesh;
	Model model;
	// NOTE: By default each cube is mapped to one part of texture atlas
	Texture2D texture;
	Vector3 mapPosition;
	// Get map image data to be used for collision detection
	Color* mapPixels;

private:
	static GameManager* GameMngr;
	Font font = { 0 };
	ScrLogo scLogo;
	ScrTitle scTitle;
	ScrOptions scOptions;
	
	ScrEnding scEnding;
	TexturesManager TextMngr = TexturesManager();
	AudioManager AudioMngr = AudioManager();


	GameScreen currentScreen;
	bool gameLoadedTextures;
};