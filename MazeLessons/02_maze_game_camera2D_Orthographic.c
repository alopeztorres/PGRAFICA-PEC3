/*******************************************************************************************
*
*   Challenge 03:   MAZE GAME
*   Lesson 02:      Camera2D Orthographic
*   Description:    Camera 2D creation and management
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

    Vector2 Texture_position = (Vector2) {screenWidth / 2 , screenHeight / 2 };
    
    // LESSON02: We load the texture used by the Cubicmap
    Camera2D camera = { 0 };
    camera.target = (Vector2){ Texture_position.x, Texture_position.y };
    camera.offset = (Vector2){ (screenWidth / 2.0f) - 80.f, screenHeight / 2.0f - Texture_position.y / 2.f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Player movement
        if (IsKeyDown(KEY_RIGHT))  Texture_position.x += 2;
        else if (IsKeyDown(KEY_LEFT)) Texture_position.x -= 2;

        if (IsKeyDown(KEY_DOWN))  Texture_position.y += 2;
        else if (IsKeyDown(KEY_UP)) Texture_position.y -= 2;

        // Camera rotation controls
        if (IsKeyDown(KEY_A)) camera.rotation--;
        else if (IsKeyDown(KEY_S)) camera.rotation++;

        // Limit camera rotation to 80 degrees (-40 to 40)
        if (camera.rotation > 40) camera.rotation = 40;
        else if (camera.rotation < -40) camera.rotation = -40;

        // Camera zoom controls
        camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        // Camera reset (zoom and rotation)
        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        DrawTexture(texture, Texture_position.x, Texture_position.y, WHITE);

        EndMode2D();

        // LESSON02: Instructions to move the camera2D.
        DrawText("Free 2d camera controls:", 20, 20, 10, BLACK);
        DrawText("- Right/Left to move Offset", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
        DrawText("- A / S to Rotate", 40, 80, 10, DARKGRAY);
        DrawText("- R to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);

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