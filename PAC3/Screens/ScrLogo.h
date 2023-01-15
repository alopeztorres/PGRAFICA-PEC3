#pragma once
#include "../GlobalDefines.h"
#include "../TexturesManager.h"


class GameManager;

class ScrLogo {
private:
    Vector2 position;
    int framesCounter = 0;
    Texture2D* texture;
    GameManager* gm;

public:
    void Init();
    void Draw();
    void Update();
    void Unload();
};