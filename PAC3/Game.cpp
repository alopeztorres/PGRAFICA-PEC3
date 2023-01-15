/*******************************************************************************************
*
*   PEC3:   MAZE3D
*
*   This game has been created using raylib 4.2 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   By: 2023 Andres Lopez Torres
*
********************************************************************************************/

#include "raylib.h"
#include "GameManager.h"


//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    //GAME TIME
    double currentGameTime = 0.f;
    double initialGameTime = 0.f;
    double time_span = 0.f;


    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "MAZE3D PAC 3");

    GameManager& GameMngr = GameManager::GetGameManager();
    GameMngr.InitGame();

    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        currentGameTime = GetTime();
        time_span = (currentGameTime - initialGameTime);

        int seconds = (int)time_span % 60;

        //Update Frame
        GameMngr.UpdateFrame(seconds);

        //Draw Frame
        GameMngr.GetGameManager().DrawFrame();
    }

    // De-Initialization
    GameMngr.UnloadGame();

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}