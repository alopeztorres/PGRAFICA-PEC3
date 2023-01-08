/*******************************************************************************************
*
*   Challenge 03:   MAZE GAME
*   Lesson 04:      Loading the textures and  the cubicmap
*   Description:    Loading a cubicmap
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

    // LESSON 03: Define the camera to look into our 3d world (Next chapter will explain it more thoroughly)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type


    // LESSON04: We load the texture used by the Cubicmap
    Image imMap = LoadImage("resources/cubicmap.png");      // Load cubicmap image (RAM)
    Texture2D cubicmap = LoadTextureFromImage(imMap);       // Convert image to texture to display (VRAM)

    Mesh mesh = GenMeshCubicmap(imMap, (Vector3) { 1.0f, 1.0f, 1.0f });
    Model model = LoadModelFromMesh(mesh);

    // NOTE: By default each cube is mapped to one part of texture atlas
    Texture2D texture = LoadTexture("resources/cubemap_atlas.png");    // Load map texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;             // Set map diffuse texture

    Vector3 mapPosition = { -20.0f, .0f, -8.0f };  // Set model position

    // LESSON03: Set a free camera mode
    SetCameraMode(camera, CAMERA_FREE);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);

        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);
            DrawModel(model, mapPosition, 1.0f, WHITE);                     // Draw maze map
        EndMode3D();

        // LESSON04: Instructions to move the camera3D.
        DrawText("Free camera default controls:", 20, 20, 10, WHITE);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, WHITE);
        DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, WHITE);
        DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, WHITE);
        DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, WHITE);
        DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadTexture(cubicmap);        // Unload cubicmap texture
    UnloadTexture(texture);         // Unload map texture

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}