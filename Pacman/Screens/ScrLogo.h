#pragma once
#include "../GlobalDefines.h"
#include "../TexturesManager.h"

class ScrLogo {
private:
    Vector2 position;
    int framesCounter = 0;
    Texture2D* texture;
    //GameScreen* screen;

public:
    void Init();
    void Draw();
    void Update();
    void Unload();
};