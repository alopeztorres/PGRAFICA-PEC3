/*******************************************************************************************
*
*   Challenge 03:   MAZE GAME
*   Lesson 05:      Camera3D Projection
*   Description:    Windows creation and input
*
*
*   Copyright (c) 2017-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>           // Required for: free()

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1020;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "CHALLENGE 03: FIRST PERSON MAZE");

    // LESSON 06: Define the camera to look into our 3d world (Next chapter will be explain more thoroughly)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 4.0f, 0.5f, 4.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type


    // LESSON02: We load the texture used by the Cubicmap
    Image imMap = LoadImage("resources/cubicmap.png");      // Load cubicmap image (RAM)
    Texture2D cubicmap = LoadTextureFromImage(imMap);       // Convert image to texture to display (VRAM)


    Mesh mesh = GenMeshCubicmap(imMap, (Vector3) { 1.0f, 1.0f, 1.0f });
    Model model = LoadModelFromMesh(mesh);

    // NOTE: By default each cube is mapped to one part of texture atlas
    Texture2D texture = LoadTexture("resources/cubemap_atlas.png");    // Load map texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;             // Set map diffuse texture

    // Get map image data to be used for collision detection
    Color* mapPixels = LoadImageColors(imMap);
    UnloadImage(imMap);             // Unload image from RAM

    Vector3 mapPosition = { 0.0f, 0.0f, 0.0f };  // Set model position

    // LESSON04: Set a free camera mode
    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);

        //----------------------------------------------------------------------------------

         // Draw
         //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);
        DrawModel(model, mapPosition, 1.0f, WHITE);                     // Draw maze map
        EndMode3D();

        DrawText("First person camera default controls:", 20, 20, 10, WHITE);
        DrawText("- Move with keys: W, A, S, D", 40, 40, 10, WHITE);
        DrawText("- Mouse move to look around", 40, 60, 10, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadImageColors(mapPixels);   // Unload color array

    UnloadTexture(cubicmap);        // Unload cubicmap texture
    UnloadTexture(texture);         // Unload map texture

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}