/*******************************************************************************************
*
*   Challenge 03:   MAZE GAME
*   Lesson 06:      Init collisions in the cubicmap
*   Description:    setting the collisions
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
    const int screenWidth = 1020;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "CHALLENGE 03: FIRST PERSON MAZE");

    // LESSON 06: Define the camera to look into our 3d world (Perspective)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 1.f, 0.5f, 1.0f };     // Camera position
    camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type


    // LESSON04: We load the texture used by the Cubicmap
    Image imMap = LoadImage("resources/cubicmap.png");      // Load cubicmap image (RAM)
    Texture2D cubicmap = LoadTextureFromImage(imMap);       // Convert image to texture to display (VRAM)

    Mesh mesh = GenMeshCubicmap(imMap, (Vector3) { 1.0f, 1.0f, 1.0f });
    Model model = LoadModelFromMesh(mesh);

    // NOTE: By default each cube is mapped to one part of texture atlas
    Texture2D texture = LoadTexture("resources/cubemap_atlas.png");    // Load map texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;             // Set map diffuse texture

    // LESSON06: Get map image data to be used for collision detection
    Color* mapPixels = LoadImageColors(imMap);
    UnloadImage(imMap);             // Unload image from RAM

    Vector3 mapPosition = { 0.0f, 0.0f, 0.0f };  // Set model position

    // LESSON04: Set a first person camera mode
    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        Vector3 oldCamPos = camera.position;
        UpdateCamera(&camera);

        // LESSON 06: Collisions detection and resolution
        // Check player collision (we simplify to 2D collision detection)
        Vector2 playerPos = { camera.position.x, camera.position.z };
        float playerRadius = 0.1f;  // Collision radius (player is modelled as a cilinder for collision)

        int playerCellX = (int)(playerPos.x - mapPosition.x  + 0.5f);
        int playerCellY = (int)(playerPos.y - mapPosition.z  + 0.5f);

        // Out-of-limits security check
        if (playerCellX < 0) playerCellX = 0;
        else if (playerCellX >= imMap.width) playerCellX = imMap.width - 1;

        if (playerCellY < 0) playerCellY = 0;
        else if (playerCellY >= imMap.height) playerCellY = imMap.height - 1;

        // Check map collisions using image data and player position
        for (int y = 0; y < cubicmap.height; y++)
        {
            for (int x = 0; x < cubicmap.width; x++)
            {
                if ((mapPixels[y * cubicmap.width + x].r == 255) &&       // Collision: white pixel, only check R channel
                    (CheckCollisionCircleRec(playerPos, playerRadius,
                        (Rectangle) {
                    mapPosition.x - 0.5f + x, mapPosition.z - 0.5f + y, 1.0f, 1.0f
                })))
                {
                    // Collision detected, reset camera position
                    camera.position = oldCamPos;
                }
            }
        }

       //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);
            DrawModel(model, mapPosition, 1.0f, WHITE);                     // Draw maze map

			// debug draw, we draw a gold cube when there is a collision, and a red  cube when there is not a collision
			/*
            for (int y = 0; y < imMap.height; y++)
            {
                for (int x = 0; x < imMap.width; x++)
                {
                    if ((mapPixels[y * imMap.width + x].r == 255))
                    {
                        // Collision detected, reset camera position
                        DrawCube((Vector3) { x, 0.5f, y }, 0.2f, 0.2f, 0.2f, GOLD);
                    }
                    else
                    {
                        DrawCube((Vector3) { x, 0.5f, y }, 0.2f, 0.2f, 0.2f, RED);
                    }
                }
            }
			*/

        EndMode3D();


        // LESSON06: Instructions to move the camera3D.
        DrawText("First person camera default controls:", 20, 20, 10, WHITE);
        DrawText("- Move with keys: W, A, S, D", 40, 40, 10, WHITE);
        DrawText("- Mouse move to look around", 40, 60, 10, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // LESSON 06: Unload color array
    UnloadImageColors(mapPixels);   

    UnloadTexture(cubicmap);        // Unload cubicmap texture
    UnloadTexture(texture);         // Unload map texture

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}