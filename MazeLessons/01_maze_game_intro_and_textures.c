/*******************************************************************************************
*
*   Challenge 03:   MAZE GAME
*   Lesson 01:      Init Window and Loading the textures
*   Description:    Windows creation, input and textures.
*
*   Copyright (c) 2017-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>           // Required for: free()

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CHALLENGE 03: FIRST PERSON MAZE");

    // LESSON01: We load the texture used by the Cubicmap
    Image image = LoadImage("resources/cubemap_atlas.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    Vector2 position = Vector2Zero();   // Quad position on screen


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_DOWN))
            TraceLog(LOG_INFO, "Key down pressed");


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        // LESSON01: We draw the texture in the screen
        DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadTexture(texture);         // Unload map texture

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}