#include "GameManager.h"
#include <iostream>
#include <string>
#include <sstream>


GameManager* GameManager::GameMngr = nullptr;

GameManager& GameManager::GetGameManager()
{
    if (!GameMngr)
        GameMngr = new GameManager();

    return *GameMngr;
}

GameManager::GameManager()
{
}



void GameManager::InitGame()
{
    started = false;
    isDead = false;

    TextMngr = TexturesManager();
    AudioMngr = AudioManager();


    TextMngr.InitTexturesFiles();     // Textures
    AudioMngr.InitAudioFiles();        // Audio

    // Load global data (assets that must be available in all screens, i.e. font)
    font = LoadFont("resources/setback.png");

    // Setup and init first screen
    scLogo = ScrLogo();
    scLogo.Init();
    scTitle = ScrTitle();
    scTitle.Init();
    scOptions = ScrOptions();
    scOptions.Init();
    scEnding = ScrEnding();
    scEnding.Init();

    currentScreen = LOGO;

    // Load textures
    texPlayer = TextMngr.GetTexture(TextureType::Pacman);
    if (!texPlayer.id)
        TraceLog(LOG_INFO, "Error texture not loaded correcly");

    texTileset = TextMngr.GetTexture(TextureType::Tiles);
    if (!texTileset.id)
        TraceLog(LOG_INFO, "Error texture not loaded correcly");

    texLives = TextMngr.GetTexture(TextureType::IconLifes);
    if (!texLives.id)
        TraceLog(LOG_INFO, "Error texture not loaded correcly");


    player = Entidad();
    ghost = Entidad();

    GameSetup();
 
}
//-------------------------------------------------------
void GameManager::UpdateFrame(int secondsPassed)
{
    // Update
    //----------------------------------------------------------------------------------

    AudioMngr.UpdateIntroMusic();

        switch (currentScreen)
        {
        case LOGO:
        {
            scLogo.Update();
        } break;
        case TITLE:
        {
            scTitle.Update();
        } break;
        case OPTIONS:
        {
            scOptions.Update();

        } break;
        case GAMEPLAY:
        {
            if (!started)
            {
                if (IsKeyPressed(KEY_A))
                {
                    started = true;
                    player.SetDirection(1);
                }

                if (IsKeyPressed(KEY_D))
                {
                    started = true;
                    player.SetDirection(3);
                }
            }

            else
            {
                if (IsSoundPlaying(AudioMngr.GameStart)) {
                    StopSound(AudioMngr.GameStart);
                    AudioMngr.PlaySirenMusic(true);
                }
                
                    player.Update(false);
                    ghost.Update(true);
                    AudioMngr.UpdateSirenMusic();
            }
            AudioMngr.PlayIntroMusic(false);

            

        } break;
        case ENDING:
        {
            scEnding.Update();
        } break;
        default: break;
        }

}

//-------------------------------------------------------

void GameManager::DrawFrame(void)
{

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(BLACK);

    switch (currentScreen)
    {
    case LOGO: scLogo.Draw(); break;
    case TITLE: scTitle.Draw(); break;
    case OPTIONS: scOptions.Draw(); break;
    case GAMEPLAY: 
    {
        string str = "Score: ";
        str.append(to_string(score));
        DrawText(str.c_str(), 40, 25, 25, WHITE);

        //Eaten Dots Debug
        //str = "eaten dots: ";
        //str.append(to_string(eatenDots));
        //DrawText(str.c_str(), 400, 25, 25, WHITE);


            for (size_t i = 1; i < lives; i++)
            {
                DrawTextureRec(texLives, { 0,0,(float)texLives.width,(float)texLives.height },
                    { ((GetScreenWidth() - (float)texLives.width * 4)) + ((float)texLives.width * i)+ ((float)texLives.width * (2-lives)), 25.f }, WHITE);
            }

        DrawTilemap(tilemap, texTileset);
        player.Drawing(false);
        ghost.Drawing(true);
    }
        break;
    case ENDING: scEnding.Draw(); break;
    default: break;
    }

    EndDrawing();
}

void GameManager::GameSetup()
{
    tilemap = LoadTilemap("PacmanResources/tilemap.txt", "PacmanResources/tilemap_colliders.txt", "PacmanResources/tilemap_objects.txt");
    tilemap.tileSize = 32;
    tilemap.position = Vector2{ (float)offsetX,(float)offsetY };

    player.SetTexture(&TextMngr.GetTexture(TextureType::Pacman));
    ghost.SetTexture(&TextMngr.GetTexture(TextureType::Ghost));
    player.Init(13, 17, false);
    ghost.Init(13, 9, true);
    lives = 3;
    started = false;
    isDead = false;
    score = 0;
    eatenDots = 0;

    scEnding.SetPlayMusic(false);

    AudioMngr.PlaySoundEffect(SoundType::GameStart);
    AudioMngr.PlaySirenMusic(true);
}

//-------------------------------------------------------

void GameManager::UnloadGame(void)
{

    switch (currentScreen)
    {
    case LOGO: scLogo.Unload(); break;
    case TITLE: scTitle.Unload(); break;
    case ENDING: scEnding.Unload(); break;
    case OPTIONS: scOptions.Unload(); break;
    default: break;
    }
    // Unload player and tileset textures
    UnloadTexture(texPlayer);       // Unload player texture
    UnloadTexture(texTileset);      // Unload tileset texture

    // Unload global data loaded
    UnloadFont(font);

    CloseAudioDevice();     // Close audio context
}


//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
void GameManager::ChangeToScreen(int screen)
{
    // Unload current screen
    switch (currentScreen)
    {
    case LOGO: scLogo.Unload(); break;
    case TITLE: scTitle.Unload(); break;
    case ENDING: scEnding.Unload(); break;
    case OPTIONS: scOptions.Unload(); break;
    default: break;
    }

    // Init next screen
    switch (screen)
    {
    case LOGO: scLogo.Init(); break;
    case TITLE: scTitle.Init(); break;
    case ENDING: scEnding.Init(); break;
    case OPTIONS: scOptions.Init(); break;
    default: break;
    }

    currentScreen = (GameScreen)screen;
}

// LESSON 05: Tilemap data loading and drawing
//----------------------------------------------------------------------------------
// Load tilemap data from file (text/image)
Tilemap GameManager::LoadTilemap(const char* valuesMap, const char* collidersMap, const char* objectsMap)
{
    Tilemap map = { 0 };
    const char* fileExt;
    const char* fileExt2;

    if ((fileExt = strrchr(valuesMap, '.')) != NULL && (fileExt2 = strrchr(objectsMap, '.')) != NULL)
    {
        // Check if file extension is supported
        if (strcmp(fileExt, ".txt") == 0 && strcmp(fileExt2, ".txt")==0)
        {
            int counter = 0;
            int temp = 0;

            // Read values from text file
            FILE* valuesFile = fopen(valuesMap, "rt");

            while (!feof(valuesFile))
            {
                fscanf(valuesFile, "%i", &temp);
                counter++;
            }

            rewind(valuesFile);        // Return to the beginning of the file, to read again

            map.tiles = (Tile*)malloc(counter * sizeof(Tile));

            map.tileCountX = 27;
            map.tileCountY = 23;
            counter = 0;

            while (!feof(valuesFile))
            {
                fscanf(valuesFile, "%i", &map.tiles[counter].value);
                counter++;
            }

            fclose(valuesFile);

            counter = 0;
            temp = 0;

            // Read values from Objects text file
            FILE* objectsFile = fopen(objectsMap, "rt");

            while (!feof(objectsFile))
            {
                fscanf(objectsFile, "%i", &temp);
                counter++;
            }

            rewind(objectsFile);        // Return to the beginning of the file, to read again

            map.objectTiles = (Tile*)malloc(counter * sizeof(Tile));

            map.tileCountX = 27;
            map.tileCountY = 23;
            counter = 0;

            while (!feof(objectsFile))
            {
                fscanf(objectsFile, "%i", &map.objectTiles[counter].value);
                counter++;
            }

            fclose(objectsFile);

            // Read values from text file
            // NOTE: Colliders map data MUST match values data, 
            // or we need to do a previous check like done with values data
            FILE* collidersFile = fopen(collidersMap, "rt");
            counter = 0;
            temp = 0;

            while (!feof(collidersFile))
            {
                fscanf(collidersFile, "%i", &temp);
                map.tiles[counter].collider = temp;

                counter++;
            }

            fclose(collidersFile);

#if DEBUG   // print tilemap information loaded
            for (int j = 0; j < map.tileCountY; j++)
            {
                for (int i = 0; i < map.tileCountX; i++)
                {
                    printf("%i ", map.tiles[j * map.tileCountX + i].collider);
                }

                printf("\n");
            }
#endif
        }
    }

    return map;
}


// Unload tilemap data from memory
void GameManager::UnloadTilemap(Tilemap map)
{
    if (map.tiles != NULL) free(map.tiles);
}

// Draw tilemap using tileset
void GameManager::DrawTilemap(Tilemap map, Texture2D tileset)
{
    for (int y = 0; y < map.tileCountY; y++)
    {
        for (int x = 0; x < map.tileCountX; x++)
        {
            // Draw each piece of the tileset in the right position to build map
            DrawTextureRec(tileset, pacmanTilesetRecs[map.tiles[y * map.tileCountX + x].value - 1],
                Vector2{
                map.position.x + x * map.tileSize, map.position.y + y * map.tileSize
                }, WHITE);

            DrawTextureRec(tileset, pacmanTilesetRecs[map.objectTiles[y * map.tileCountX + x].value - 1],
                Vector2{
                map.position.x + x * map.tileSize, map.position.y + y * map.tileSize
                }, WHITE);
        }
    }

}

Tilemap* GameManager::GetTilemap() 
{
    return &tilemap;
}

BehaviorState GameManager::GetGhostState()
{
    return ghostState;
}

void GameManager::SetGhostState(BehaviorState state)
{
    ghostState = state;
}

Entidad* GameManager::GetGhost()
{
    return &ghost;
}

Entidad* GameManager::GetPlayer()
{
    return &player;
}