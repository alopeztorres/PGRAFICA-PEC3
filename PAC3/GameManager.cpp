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

void GameManager::UnloadObjects()
{
    for (size_t i = 0; i < objList.size(); ++i)
    {
        TODELETE(objList[i]);
    }
}

void GameManager::UnloadProps()
{
    for (size_t i = 0; i < propList.size(); ++i)
    {
        TODELETE(propList[i]);
    }
}

GameManager::GameManager()
{
}

void GameManager::LoadLevel(int levelNumber)
{
    //UnloadObjects();


    if (levelNumber == 1)
    {
        camera.position = Vector3{ 1.f, 0.5f, 1.0f };  // Camera position
        camera.target = Vector3{ 0.0f, 1.8f, 0.0f };      // Camera looking at point
        camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
        camera.fovy = 45.0f;                                // Camera field-of-view Y
        camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type


        // LESSON04: We load the texture used by the Cubicmap
        imMap = LoadImage("PAC3Resources/map1.png");      // Load cubicmap image (RAM)
        cubicmap = LoadTextureFromImage(imMap);       // Convert image to texture to display (VRAM)

        mesh = GenMeshCubicmapV2(imMap, Vector3{ 1.0f, 1.0f, 1.0f });
        model = LoadModelFromMesh(mesh);

        // NOTE: By default each cube is mapped to one part of texture atlas
        texture = LoadTexture("PAC3Resources/cubemap_atlasFull.png");    // Load map texture
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;             // Set map diffuse texture

        // Get map image data to be used for collision detection
        mapPixels = LoadImageColors(imMap);
        UnloadImage(imMap);             // Unload image from RAM

        mapPosition = { 0.0f, 0.0f, 0.0f };  // Set model position



        BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);   // Set model bounds

        // LESSON05: Set a free camera mode
        SetCameraMode(camera, CAMERA_FIRST_PERSON);
    }

    if (levelNumber == 2)
    {
        camera.position = Vector3{ 1.f, 0.5f, 1.0f };  // Camera position
        camera.target = Vector3{ 0.0f, 1.8f, 0.0f };      // Camera looking at point
        camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
        camera.fovy = 45.0f;                                // Camera field-of-view Y
        camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type


        // LESSON04: We load the texture used by the Cubicmap
        imMap = LoadImage("PAC3Resources/cubicmap.png");      // Load cubicmap image (RAM)
        cubicmap = LoadTextureFromImage(imMap);       // Convert image to texture to display (VRAM)

        mesh = GenMeshCubicmapV2(imMap, Vector3{ 1.0f, 1.0f, 1.0f });
        model = LoadModelFromMesh(mesh);

        // NOTE: By default each cube is mapped to one part of texture atlas
        texture = LoadTexture("PAC3Resources/cubemap_atlasFull.png");    // Load map texture
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;             // Set map diffuse texture

        // Get map image data to be used for collision detection
        mapPixels = LoadImageColors(imMap);
        UnloadImage(imMap);             // Unload image from RAM

        mapPosition = { 0.0f, 0.0f, 0.0f };  // Set model position

        //Adding the props to a list
        //AddProp("MazeResources/models/obj/castle.obj", "MazeResources/models/obj/castle_diffuse.png", "castle");
        //AddProp("MazeResources/models/obj/house.obj", "MazeResources/models/obj/house_diffuse.png", "house");
        //AddProp("PAC3Resources/models/obj/door.obj", "PAC3Resources/models/obj/door_diffuse.png", "door");

        BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);   // Set model bounds

        // LESSON05: Set a free camera mode
        SetCameraMode(camera, CAMERA_FIRST_PERSON);
    }
}


void GameManager::InitGame()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    //Adding the props to a list
    AddProp("MazeResources/models/obj/castle.obj", "MazeResources/models/obj/castle_diffuse.png", "castle");
    AddProp("MazeResources/models/obj/house.obj", "MazeResources/models/obj/house_diffuse.png", "house");
    AddProp("PAC3Resources/models/obj/door.obj", "PAC3Resources/models/obj/door_diffuse.png", "door");

    currentScreen = LOADING;

    currentLevel = 1;
    //const int MaxObjs = 1;

    // Prop objs[] = { MaxObjs };
    // Prop objs = Prop();
     //Prop objs[] = { LoadModel("MazeResources/models/obj/castle.obj"),LoadTexture("MazeResources/models/obj/castle_diffuse.png") };
     //objs.model = LoadModel("MazeResources/models/obj/castle.obj");                 // Load model
     //objs.text = LoadTexture("MazeResources/models/obj/castle_diffuse.png"); // Load model texture

    //InitWindow(screenWidth, screenHeight, "CHALLENGE 03: FIRST PERSON MAZE");

    // LESSON 05: Define the camera to look into our 3d world (Next chapter will be explain more thoroughly)
    


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    GameSetup();
 
}
//-------------------------------------------------------
void GameManager::UpdateFrame(int secondsPassed)
{
    // Update
    //----------------------------------------------------------------------------------

    //AudioMngr.UpdateIntroMusic();

    switch (currentScreen)
    {
    case LOADING:
    {
        scLoading.Update();
    } break;

    case GAMEPLAY:
    {
        // Update
           //----------------------------------------------------------------------------------
        Vector3 oldCamPos = camera.position;
        UpdateCamera(&camera);

        // LESSON 07: Collisions detection and resolution
        // Check player collision (we simplify to 2D collision detection)
        Vector2 playerPos = { camera.position.x, camera.position.z };
        float playerRadius = 0.1f;  // Collision radius (player is modelled as a cilinder for collision)

        int playerCellX = (int)(playerPos.x - mapPosition.x + 0.5f);
        int playerCellY = (int)(playerPos.y - mapPosition.z + 0.5f);

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
                        Rectangle{
                    mapPosition.x - 0.5f + x, mapPosition.z - 0.5f + y, 1.0f, 1.0f
                        })))
                {
                    // Collision detected, reset camera position
                    camera.position = oldCamPos;
                }
            }
        }

        //Props Collision Check
        for (int i = 0; i < objList.size(); i++)
        {
            if ((objList[i]->collider) &&       // If object has bool collider true
                (CheckCollisionCircleRec(playerPos, playerRadius,
                    Rectangle{
                objList[i]->position.x - 0.5f, objList[i]->position.z - 0.5f, 1.0f, 1.0f
                    })))
            {
                // Collision detected, reset camera position
                camera.position = oldCamPos;
            }

            //Reaching Ending Level Condition
            if ((objList[i]->exit) &&       // If object has bool exit true, then load the new Level
                (CheckCollisionCircleRec(playerPos, playerRadius,
                    Rectangle{
                objList[i]->position.x - 0.5f, objList[i]->position.z - 0.5f, 1.0f, 1.0f
                    })))
            {
                // Collision detected, reset camera position
                ChangeToScreen(GameScreen::LOADING);  // GAMEPLAY
                if(currentLevel==1)
                currentLevel = 2;
                else
                    currentLevel = 1;
                UnloadImageColors(mapPixels);   // Unload color array
                UnloadTexture(cubicmap);        // Unload cubicmap texture
                UnloadTexture(texture);         // Unload map texture
                UnloadModel(model);
            }
        }


    }
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
    case LOADING: scLoading.Draw(); break;

    case GAMEPLAY:
    {
        BeginMode3D(camera);

        // LESSON04: Draw maze map
        DrawModel(model, mapPosition, 1.0f, WHITE);

        // LESSON07: Draw Model
        //DrawModel(modelCastle, modelposition, 0.02f, WHITE);        // Draw 3d model with texture
        RenderProps();

        EndMode3D();

        // LESSON05: Instructions to move the camera3D.
        DrawText("First person camera default controls:", 20, 20, 10, WHITE);
        DrawText("- Move with keys: W, A, S, D", 40, 40, 10, WHITE);
        DrawText("- Mouse move to look around", 40, 60, 10, WHITE);
        for (int i = 0; i < objList.size(); i++)
        {
            DrawText(std::to_string(objList[i]->modelType).c_str(), 40, 80 + (i * 20), 10, WHITE);
        }



    }

    /*
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
    */
    }
    EndDrawing();
}

void GameManager::GameSetup()
{
    /*
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
    */
}

//-------------------------------------------------------

void GameManager::UnloadGame(void)
{
    /*
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

    // 

    CloseAudioDevice();     // Close audio context
    */

    UnloadImageColors(mapPixels);   // Unload color array
    UnloadTexture(cubicmap);        // Unload cubicmap texture
    UnloadTexture(texture);         // Unload map texture


    UnloadProps();
    UnloadObjects();

    //CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}


//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
void GameManager::ChangeToScreen(int screen)
{
    /*
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
    */
    currentScreen = (GameScreen)screen;
    
}

// Generate a cubes mesh from pixel data
// NOTE: Vertex data is uploaded to GPU
Mesh GameManager::GenMeshCubicmapV2(Image cubicmap, Vector3 cubeSize)
{
#define COLOR_EQUAL(col1, col2) ((col1.r == col2.r)&&(col1.g == col2.g)&&(col1.b == col2.b)&&(col1.a == col2.a))

    Mesh mesh = { 0 };

    int numTex = 2;
    int texAmount = 2;

    Color* pixels = LoadImageColors(cubicmap);

    int mapWidth = cubicmap.width;
    int mapHeight = cubicmap.height;

    // NOTE: Max possible number of triangles numCubes*(12 triangles by cube)
    int maxTriangles = cubicmap.width * cubicmap.height * 12;

    int vCounter = 0;       // Used to count vertices
    int tcCounter = 0;      // Used to count texcoords
    int nCounter = 0;       // Used to count normals

    float w = cubeSize.x;
    float h = cubeSize.z;
    float h2 = cubeSize.y;

    Vector3* mapVertices = (Vector3*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector3));
    Vector2* mapTexcoords = (Vector2*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector2));
    Vector3* mapNormals = (Vector3*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector3));

    // Define the 6 normals of the cube, we will combine them accordingly later...
    Vector3 n1 = { 1.0f, 0.0f, 0.0f };
    Vector3 n2 = { -1.0f, 0.0f, 0.0f };
    Vector3 n3 = { 0.0f, 1.0f, 0.0f };
    Vector3 n4 = { 0.0f, -1.0f, 0.0f };
    Vector3 n5 = { 0.0f, 0.0f, -1.0f };
    Vector3 n6 = { 0.0f, 0.0f, 1.0f };

    // NOTE: We use texture rectangles to define different textures for top-bottom-front-back-right-left (6)
    typedef struct RectangleF {
        float x;
        float y;
        float width;
        float height;
    } RectangleF;

    float calc1 = (float)0.5f / texAmount;
    float calc2 = (texAmount - 1) - (numTex % texAmount);

    /*
    RectangleF rightTexUV = {calc2*0.5f, calc2 * 0.5f, calc1, calc1 };
    RectangleF leftTexUV = { calc1+ calc2 * 0.5f, calc2 * 0.5f, calc1, calc1 };
    RectangleF frontTexUV = { calc2 * 0.5f, calc2 * 0.5f, calc1, calc1 };
    RectangleF backTexUV = { calc1, calc2 * 0.5f, calc1, calc1 };
    RectangleF topTexUV = { calc2 * 0.5f, calc1+ calc2 * 0.5f, calc1, calc1 };
    RectangleF bottomTexUV = { calc1+ calc2 * 0.5f, calc1+ calc2 * 0.5f, calc1, calc1 };
    */

    RectangleF rightTexUV = { 0.0f, 0.0f, 0.25f, 0.25f };
    RectangleF leftTexUV = { 0.25f, 0.0f, 0.25f, 0.25f };
    RectangleF frontTexUV = { 0.0f, 0.0f, 0.25f, 0.25f };
    RectangleF backTexUV = { 0.25f, 0.0f, 0.25f, 0.25f };
    RectangleF topTexUV = { 0.0f, 0.25f, 0.25f, 0.25f };
    RectangleF bottomTexUV = { 0.25f, 0.25f, 0.25f, 0.25f };


    /*
    //si es b1
    rightTexUV = { 0.5f, 0.0f, 0.25f, 0.25f };
    leftTexUV = { 0.75f, 0.0f, 0.25f, 0.25f };
    frontTexUV = { 0.5f, 0.0f, 0.25f, 0.25f };
    backTexUV = { 0.75f, 0.0f, 0.25f, 0.25f };
    topTexUV = { 0.5f, 0.25f, 0.25f, 0.25f };
    bottomTexUV = { 0.75f, 0.25f, 0.25f, 0.25f };


    // si es b2
    rightTexUV = { 0.5f, 0.5f, 0.25f, 0.25f };
    leftTexUV = { 0.75f, 0.5f, 0.25f, 0.25f };
    frontTexUV = { 0.5f, 0.5f, 0.25f, 0.25f };
    backTexUV = { 0.75f, 0.5f, 0.25f, 0.25f };
    topTexUV = { 0.5f, 0.75f, 0.25f, 0.25f };
    bottomTexUV = { 0.75f, 0.75f, 0.25f, 0.25f };


    // si es b3
    rightTexUV = { 0.0f, 0.5f, 0.25f, 0.25f };
    leftTexUV = { 0.25f, 0.5f, 0.25f, 0.25f };
    frontTexUV = { 0.0f, 0.5f, 0.25f, 0.25f };
    backTexUV = { 0.25f, 0.5f, 0.25f, 0.25f };
    topTexUV = { 0.0f, 0.75f, 0.25f, 0.25f };
    bottomTexUV = { 0.25f, 0.75f, 0.25f, 0.25f };
    */

    for (int z = 0; z < mapHeight; ++z)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            // Define the 8 vertex of the cube, we will combine them accordingly later...
            Vector3 v1 = { w * (x - 0.5f), h2, h * (z - 0.5f) };
            Vector3 v2 = { w * (x - 0.5f), h2, h * (z + 0.5f) };
            Vector3 v3 = { w * (x + 0.5f), h2, h * (z + 0.5f) };
            Vector3 v4 = { w * (x + 0.5f), h2, h * (z - 0.5f) };
            Vector3 v5 = { w * (x + 0.5f), 0, h * (z - 0.5f) };
            Vector3 v6 = { w * (x - 0.5f), 0, h * (z - 0.5f) };
            Vector3 v7 = { w * (x - 0.5f), 0, h * (z + 0.5f) };
            Vector3 v8 = { w * (x + 0.5f), 0, h * (z + 0.5f) };


            switch (pixels[z * cubicmap.width + x].b)
            {
            case 0:
                rightTexUV = { 0.0f, 0.0f, 0.25f, 0.25f };
                leftTexUV = { 0.25f, 0.0f, 0.25f, 0.25f };
                frontTexUV = { 0.0f, 0.0f, 0.25f, 0.25f };
                backTexUV = { 0.25f, 0.0f, 0.25f, 0.25f };
                topTexUV = { 0.0f, 0.25f, 0.25f, 0.25f };
                bottomTexUV = { 0.25f, 0.25f, 0.25f, 0.25f };
                break;

            case 1:
                rightTexUV = { 0.5f, 0.0f, 0.25f, 0.25f };
                leftTexUV = { 0.75f, 0.0f, 0.25f, 0.25f };
                frontTexUV = { 0.5f, 0.0f, 0.25f, 0.25f };
                backTexUV = { 0.75f, 0.0f, 0.25f, 0.25f };
                topTexUV = { 0.5f, 0.25f, 0.25f, 0.25f };
                bottomTexUV = { 0.75f, 0.25f, 0.25f, 0.25f };
                break;

            case 2:
                rightTexUV = { 0.5f, 0.5f, 0.25f, 0.25f };
                leftTexUV = { 0.75f, 0.5f, 0.25f, 0.25f };
                frontTexUV = { 0.5f, 0.5f, 0.25f, 0.25f };
                backTexUV = { 0.75f, 0.5f, 0.25f, 0.25f };
                topTexUV = { 0.5f, 0.75f, 0.25f, 0.25f };
                bottomTexUV = { 0.75f, 0.75f, 0.25f, 0.25f };
                break;

            case 3:
                rightTexUV = { 0.0f, 0.5f, 0.25f, 0.25f };
                leftTexUV = { 0.25f, 0.5f, 0.25f, 0.25f };
                frontTexUV = { 0.0f, 0.5f, 0.25f, 0.25f };
                backTexUV = { 0.25f, 0.5f, 0.25f, 0.25f };
                topTexUV = { 0.0f, 0.75f, 0.25f, 0.25f };
                bottomTexUV = { 0.25f, 0.75f, 0.25f, 0.25f };
                break;

            default:
                break;
            }

            if ((pixels[z * cubicmap.width + x].r == 128))
            {
                ObjDetails* objList = new ObjDetails;
                bool flag = false;
                switch (pixels[z * cubicmap.width + x].g)
                {
                case 1:
                    objList->modelType = 0;
                    objList->position = { (float)x,0,(float)z };
                    objList->collider = true;
                    flag = true;
                    break;

                case 2:
                    objList->modelType = 1;
                    objList->position = { (float)x,0,(float)z };
                    objList->collider = false;
                    flag = true;
                    break;

                case 3:
                    objList->modelType = 2;
                    objList->position = { (float)x,0,(float)z };
                    objList->collider = false;
                    objList->exit = true;
                    flag = true;
                    break;
                }
                if (flag)
                    AddObj(objList);
            }

            // We check pixel color to be WHITE -> draw full cube
            if ((pixels[z * cubicmap.width + x].r == 255))
            {
                // Define triangles and checking collateral cubes
                //------------------------------------------------

                // Define top triangles (2 tris, 6 vertex --> v1-v2-v3, v1-v3-v4)
                // WARNING: Not required for a WHITE cubes, created to allow seeing the map from outside
                mapVertices[vCounter] = v1;
                mapVertices[vCounter + 1] = v2;
                mapVertices[vCounter + 2] = v3;
                mapVertices[vCounter + 3] = v1;
                mapVertices[vCounter + 4] = v3;
                mapVertices[vCounter + 5] = v4;
                vCounter += 6;

                mapNormals[nCounter] = n3;
                mapNormals[nCounter + 1] = n3;
                mapNormals[nCounter + 2] = n3;
                mapNormals[nCounter + 3] = n3;
                mapNormals[nCounter + 4] = n3;
                mapNormals[nCounter + 5] = n3;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ topTexUV.x, topTexUV.y };
                mapTexcoords[tcCounter + 1] = Vector2{ topTexUV.x, topTexUV.y + topTexUV.height };
                mapTexcoords[tcCounter + 2] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
                mapTexcoords[tcCounter + 3] = Vector2{ topTexUV.x, topTexUV.y };
                mapTexcoords[tcCounter + 4] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
                mapTexcoords[tcCounter + 5] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y };
                tcCounter += 6;

                // Define bottom triangles (2 tris, 6 vertex --> v6-v8-v7, v6-v5-v8)
                mapVertices[vCounter] = v6;
                mapVertices[vCounter + 1] = v8;
                mapVertices[vCounter + 2] = v7;
                mapVertices[vCounter + 3] = v6;
                mapVertices[vCounter + 4] = v5;
                mapVertices[vCounter + 5] = v8;
                vCounter += 6;

                mapNormals[nCounter] = n4;
                mapNormals[nCounter + 1] = n4;
                mapNormals[nCounter + 2] = n4;
                mapNormals[nCounter + 3] = n4;
                mapNormals[nCounter + 4] = n4;
                mapNormals[nCounter + 5] = n4;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
                mapTexcoords[tcCounter + 1] = Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
                mapTexcoords[tcCounter + 2] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y + bottomTexUV.height };
                mapTexcoords[tcCounter + 3] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
                mapTexcoords[tcCounter + 4] = Vector2{ bottomTexUV.x, bottomTexUV.y };
                mapTexcoords[tcCounter + 5] = Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
                tcCounter += 6;

                // Checking cube on bottom of current cube
                if (((z < cubicmap.height - 1) && (pixels[z * cubicmap.width + x].r == 255)) || (z == cubicmap.height - 1))
                {
                    // Define front triangles (2 tris, 6 vertex) --> v2 v7 v3, v3 v7 v8
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v2;
                    mapVertices[vCounter + 1] = v7;
                    mapVertices[vCounter + 2] = v3;
                    mapVertices[vCounter + 3] = v3;
                    mapVertices[vCounter + 4] = v7;
                    mapVertices[vCounter + 5] = v8;
                    vCounter += 6;

                    mapNormals[nCounter] = n6;
                    mapNormals[nCounter + 1] = n6;
                    mapNormals[nCounter + 2] = n6;
                    mapNormals[nCounter + 3] = n6;
                    mapNormals[nCounter + 4] = n6;
                    mapNormals[nCounter + 5] = n6;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ frontTexUV.x, frontTexUV.y };
                    mapTexcoords[tcCounter + 1] = Vector2{ frontTexUV.x, frontTexUV.y + frontTexUV.height };
                    mapTexcoords[tcCounter + 2] = Vector2{ frontTexUV.x + frontTexUV.width, frontTexUV.y };
                    mapTexcoords[tcCounter + 3] = Vector2{ frontTexUV.x + frontTexUV.width, frontTexUV.y };
                    mapTexcoords[tcCounter + 4] = Vector2{ frontTexUV.x, frontTexUV.y + frontTexUV.height };
                    mapTexcoords[tcCounter + 5] = Vector2{ frontTexUV.x + frontTexUV.width, frontTexUV.y + frontTexUV.height };
                    tcCounter += 6;
                }

                // Checking cube on top of current cube
                if (((z > 0) && (pixels[z * cubicmap.width + x].r == 255)) || (z == 0))
                {
                    // Define back triangles (2 tris, 6 vertex) --> v1 v5 v6, v1 v4 v5
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v1;
                    mapVertices[vCounter + 1] = v5;
                    mapVertices[vCounter + 2] = v6;
                    mapVertices[vCounter + 3] = v1;
                    mapVertices[vCounter + 4] = v4;
                    mapVertices[vCounter + 5] = v5;
                    vCounter += 6;

                    mapNormals[nCounter] = n5;
                    mapNormals[nCounter + 1] = n5;
                    mapNormals[nCounter + 2] = n5;
                    mapNormals[nCounter + 3] = n5;
                    mapNormals[nCounter + 4] = n5;
                    mapNormals[nCounter + 5] = n5;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ backTexUV.x + backTexUV.width, backTexUV.y };
                    mapTexcoords[tcCounter + 1] = Vector2{ backTexUV.x, backTexUV.y + backTexUV.height };
                    mapTexcoords[tcCounter + 2] = Vector2{ backTexUV.x + backTexUV.width, backTexUV.y + backTexUV.height };
                    mapTexcoords[tcCounter + 3] = Vector2{ backTexUV.x + backTexUV.width, backTexUV.y };
                    mapTexcoords[tcCounter + 4] = Vector2{ backTexUV.x, backTexUV.y };
                    mapTexcoords[tcCounter + 5] = Vector2{ backTexUV.x, backTexUV.y + backTexUV.height };
                    tcCounter += 6;
                }

                // Checking cube on right of current cube
                if (((x < cubicmap.width - 1) && (pixels[z * cubicmap.width + x].r == 255)) || (x == cubicmap.width - 1))
                {
                    // Define right triangles (2 tris, 6 vertex) --> v3 v8 v4, v4 v8 v5
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v3;
                    mapVertices[vCounter + 1] = v8;
                    mapVertices[vCounter + 2] = v4;
                    mapVertices[vCounter + 3] = v4;
                    mapVertices[vCounter + 4] = v8;
                    mapVertices[vCounter + 5] = v5;
                    vCounter += 6;

                    mapNormals[nCounter] = n1;
                    mapNormals[nCounter + 1] = n1;
                    mapNormals[nCounter + 2] = n1;
                    mapNormals[nCounter + 3] = n1;
                    mapNormals[nCounter + 4] = n1;
                    mapNormals[nCounter + 5] = n1;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ rightTexUV.x, rightTexUV.y };
                    mapTexcoords[tcCounter + 1] = Vector2{ rightTexUV.x, rightTexUV.y + rightTexUV.height };
                    mapTexcoords[tcCounter + 2] = Vector2{ rightTexUV.x + rightTexUV.width, rightTexUV.y };
                    mapTexcoords[tcCounter + 3] = Vector2{ rightTexUV.x + rightTexUV.width, rightTexUV.y };
                    mapTexcoords[tcCounter + 4] = Vector2{ rightTexUV.x, rightTexUV.y + rightTexUV.height };
                    mapTexcoords[tcCounter + 5] = Vector2{ rightTexUV.x + rightTexUV.width, rightTexUV.y + rightTexUV.height };
                    tcCounter += 6;
                }

                // Checking cube on left of current cube
                if (((x > 0) && (pixels[z * cubicmap.width + x].r == 255)) || (x == 0))
                {
                    // Define left triangles (2 tris, 6 vertex) --> v1 v7 v2, v1 v6 v7
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v1;
                    mapVertices[vCounter + 1] = v7;
                    mapVertices[vCounter + 2] = v2;
                    mapVertices[vCounter + 3] = v1;
                    mapVertices[vCounter + 4] = v6;
                    mapVertices[vCounter + 5] = v7;
                    vCounter += 6;

                    mapNormals[nCounter] = n2;
                    mapNormals[nCounter + 1] = n2;
                    mapNormals[nCounter + 2] = n2;
                    mapNormals[nCounter + 3] = n2;
                    mapNormals[nCounter + 4] = n2;
                    mapNormals[nCounter + 5] = n2;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ leftTexUV.x, leftTexUV.y };
                    mapTexcoords[tcCounter + 1] = Vector2{ leftTexUV.x + leftTexUV.width, leftTexUV.y + leftTexUV.height };
                    mapTexcoords[tcCounter + 2] = Vector2{ leftTexUV.x + leftTexUV.width, leftTexUV.y };
                    mapTexcoords[tcCounter + 3] = Vector2{ leftTexUV.x, leftTexUV.y };
                    mapTexcoords[tcCounter + 4] = Vector2{ leftTexUV.x, leftTexUV.y + leftTexUV.height };
                    mapTexcoords[tcCounter + 5] = Vector2{ leftTexUV.x + leftTexUV.width, leftTexUV.y + leftTexUV.height };
                    tcCounter += 6;
                }
            }
            // We check pixel color to be BLACK, we will only draw floor and roof
            //Solo si R es igual a 0
            //else if (COLOR_EQUAL(pixels[z * cubicmap.width + x], BLACK))
            else if (pixels[z * cubicmap.width + x].r == 0 || (pixels[z * cubicmap.width + x].r == 128))
            {
                // Define top triangles (2 tris, 6 vertex --> v1-v2-v3, v1-v3-v4)
                mapVertices[vCounter] = v1;
                mapVertices[vCounter + 1] = v3;
                mapVertices[vCounter + 2] = v2;
                mapVertices[vCounter + 3] = v1;
                mapVertices[vCounter + 4] = v4;
                mapVertices[vCounter + 5] = v3;
                vCounter += 6;

                mapNormals[nCounter] = n4;
                mapNormals[nCounter + 1] = n4;
                mapNormals[nCounter + 2] = n4;
                mapNormals[nCounter + 3] = n4;
                mapNormals[nCounter + 4] = n4;
                mapNormals[nCounter + 5] = n4;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ topTexUV.x, topTexUV.y };
                mapTexcoords[tcCounter + 1] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
                mapTexcoords[tcCounter + 2] = Vector2{ topTexUV.x, topTexUV.y + topTexUV.height };
                mapTexcoords[tcCounter + 3] = Vector2{ topTexUV.x, topTexUV.y };
                mapTexcoords[tcCounter + 4] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y };
                mapTexcoords[tcCounter + 5] = Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
                tcCounter += 6;

                // Define bottom triangles (2 tris, 6 vertex --> v6-v8-v7, v6-v5-v8)
                mapVertices[vCounter] = v6;
                mapVertices[vCounter + 1] = v7;
                mapVertices[vCounter + 2] = v8;
                mapVertices[vCounter + 3] = v6;
                mapVertices[vCounter + 4] = v8;
                mapVertices[vCounter + 5] = v5;
                vCounter += 6;

                mapNormals[nCounter] = n3;
                mapNormals[nCounter + 1] = n3;
                mapNormals[nCounter + 2] = n3;
                mapNormals[nCounter + 3] = n3;
                mapNormals[nCounter + 4] = n3;
                mapNormals[nCounter + 5] = n3;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
                mapTexcoords[tcCounter + 1] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y + bottomTexUV.height };
                mapTexcoords[tcCounter + 2] = Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
                mapTexcoords[tcCounter + 3] = Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
                mapTexcoords[tcCounter + 4] = Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
                mapTexcoords[tcCounter + 5] = Vector2{ bottomTexUV.x, bottomTexUV.y };
                tcCounter += 6;
            }


        }
    }

    // Move data from mapVertices temp arays to vertices float array
    mesh.vertexCount = vCounter;
    mesh.triangleCount = vCounter / 3;

    mesh.vertices = (float*)RL_MALLOC(mesh.vertexCount * 3 * sizeof(float));
    mesh.normals = (float*)RL_MALLOC(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float*)RL_MALLOC(mesh.vertexCount * 2 * sizeof(float));
    mesh.colors = NULL;

    int fCounter = 0;

    // Move vertices data
    for (int i = 0; i < vCounter; i++)
    {
        mesh.vertices[fCounter] = mapVertices[i].x;
        mesh.vertices[fCounter + 1] = mapVertices[i].y;
        mesh.vertices[fCounter + 2] = mapVertices[i].z;
        fCounter += 3;
    }

    fCounter = 0;

    // Move normals data
    for (int i = 0; i < nCounter; i++)
    {
        mesh.normals[fCounter] = mapNormals[i].x;
        mesh.normals[fCounter + 1] = mapNormals[i].y;
        mesh.normals[fCounter + 2] = mapNormals[i].z;
        fCounter += 3;
    }

    fCounter = 0;

    // Move texcoords data
    for (int i = 0; i < tcCounter; i++)
    {
        mesh.texcoords[fCounter] = mapTexcoords[i].x;
        mesh.texcoords[fCounter + 1] = mapTexcoords[i].y;
        fCounter += 2;
    }

    RL_FREE(mapVertices);
    RL_FREE(mapNormals);
    RL_FREE(mapTexcoords);

    UnloadImageColors(pixels);   // Unload pixels color data

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}

