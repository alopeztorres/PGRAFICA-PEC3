#include "Entidad.h"

#include "GameManager.h"

Entidad::Entidad()
{

}

void Entidad::Update(bool isGhost)
{
    
    GameManager& gMngr = GameManager::GetGameManager();
    Entidad* player = gMngr.GetPlayer();
    Entidad* ghost = gMngr.GetGhost();

    printf("\nDead: %i", gMngr.GetDead());
    if (!isGhost)
    {
        if (!gMngr.GetDead())
        {
            int posSprite[4] = { 2,1,3,0 };
            animationCounter++;

            if (animationCounter >= (60 / framesSpeed))
            {
                animationCounter = 0;
                currentFrame++;

                if (currentFrame > 1) currentFrame = 0;

                frameRec.x = (float)currentFrame * (float)texture->width / 2;
                frameRec.y = (float)texture->height / 4 * posSprite[direction];
            }
        }
        else
        {
            if (deadframeCounter == 0)
            {
                texture = &gMngr.GetTextMngr().GetTexture(TextureType::Dead);
                animationCounter = 0;
                gMngr.GetAudioMngr().PlaySoundEffect(SoundType::Dead);
                gMngr.GetAudioMngr().PlaySirenMusic(false);
            }

            deadframeCounter++;

            animationCounter++;

            if (animationCounter >= (60 / framesSpeed))
            {
                animationCounter = 0;
                currentFrame++;

                if (currentFrame < 12)
                {
                    frameRec.x = (float)currentFrame * (float)texture->width / 12;
                }
                else {
                    frameRec = {0.0f,0.f,0.f,0.f};
                }
            }

            if (deadframeCounter > 180)
            {
                deadframeCounter = 0;
                if (gMngr.GetLives() > 0) {
                    gMngr.SetStarted(false);
                    gMngr.SetDead(false);
                    texture = &gMngr.GetTextMngr().GetTexture(TextureType::Pacman);
                    ghost->SetPos({ 13.f * tilemap->tileSize + offsetX, 9.f * tilemap->tileSize + offsetY, 32, 32 });
                    player->SetPos({ 13.f * tilemap->tileSize + offsetX, 17.f * tilemap->tileSize + offsetY, 32, 32 });
                    frameRec = { 0.0f, (float)texture->height / 4, (float)texture->width / 2, (float)texture->height / 4 };
                    gMngr.GetAudioMngr().PlaySoundEffect(SoundType::GameStart);
                    gMngr.GetAudioMngr().PlaySirenMusic(true);
                }
                else {
                    gMngr.ChangeToScreen(GameScreen::ENDING);
                }
            }

        }
    }
    else
    {
        animationCounter++;

        if (animationCounter >= (60 / framesSpeed))
        {
            animationCounter = 0;
            currentFrame++;
            if (gMngr.GetGhostState() == CHASE || gMngr.GetGhostState() == INHOME)
            {
                if (currentFrame > 1) currentFrame = 0;

                frameRec.y = 0.f;
                frameRec.x = ((float)currentFrame * (float)texture->width / 12) + (ghostAnimOffset * (float)texture->width / 12 * 2);
            }
            if (gMngr.GetGhostState() == FRIGHTENED)
            {
                if (currentFrame > 1) currentFrame = 0;
                frameRec.y = 0.f;
                frameRec.x = ((float)currentFrame * (float)texture->width / 12) + (4 * (float)texture->width / 12 * 2);
            }
            if (gMngr.GetGhostState() == EATEN)
            {
                if (currentFrame > 0) currentFrame = 0;

                frameRec.x = ((float)currentFrame * (float)texture->width / 12) + ((ghostAnimOffset + 8) * (float)texture->width / 12);
                frameRec.y = 32.f;
            }
        }
    }


    //----------------------------------------------------------------------------------
        //Warp
    if (bounds[0] < 0 && bounds[2] < 0)
    {
        pos.x += (tilemap->tileCountX + 1) * pos.width;
    }
    if (bounds[0] >= tilemap->tileCountX && bounds[2] >= tilemap->tileCountX)
    {
        pos.x -= (tilemap->tileCountX + 1) * pos.width;
    }

    memcpy(oldBounds, bounds, sizeof(int) * 4);
    memcpy(bounds, setBounds(tilemap, pos), sizeof(int) * 4);

    oldPos = pos;

    if (!isGhost)
    {
        if (!gMngr.GetDead())
        {
            CheckInput();
            ValidatePlayerCollision();
        }
    }
    else
    {

        if (!gMngr.GetDead())
        {
            if (bounds[0] == 13 && bounds[1] == 11 &&
                bounds[2] == 13 && bounds[3] == 11 && gMngr.GetGhostState() == EATEN)
            {
                direction = setGhostDir(tilemap, pos, ((direction + 2) & 3), movementSpeed, exitTarget);
                gMngr.SetGhostState(INHOME);
                movementSpeed = 1;
                ghostColor = { 0,255,0,255 };
            }

            if (bounds[0] == 13 && bounds[1] == 9 &&
                bounds[2] == 13 && bounds[3] == 9 && gMngr.GetGhostState() == INHOME)
            {
                direction = setGhostDir(tilemap, pos, direction, movementSpeed, exitTarget);
                ghostColor = { 255,0,0,255 };
                movementSpeed = 2;
                gMngr.SetGhostState(CHASE);
                framesCounter = 0;
            }


            if (bounds[0] == bounds[2] && bounds[1] == bounds[3])
            {
                //printf("\n -|| (%d,%d,%d,%d) (%d,%d,%d,%d) ", playerBounds[0], playerBounds[1], playerBounds[2], playerBounds[3], ghostBounds[0], ghostBounds[1], ghostBounds[2], ghostBounds[3]);
                if (gMngr.GetGhostState() == CHASE)
                {
                    direction = setGhostDir(tilemap, pos, direction, movementSpeed, gMngr.GetPlayer()->GetBounds());
                }
                else if (gMngr.GetGhostState() == FRIGHTENED)
                {
                    direction = setGhostDir(tilemap, pos, direction, movementSpeed, frightenedTarget);
                }
                else if (gMngr.GetGhostState() == EATEN)
                {
                    direction = setGhostDir(tilemap, pos, direction, movementSpeed, homeTarget);
                }
                else if (gMngr.GetGhostState() == INHOME)
                {
                    direction = setGhostDir(tilemap, pos, direction, movementSpeed, exitTarget);
                }
            }

            if (gMngr.GetGhostState() == FRIGHTENED)
            {
                ghostAnimOffset = 4;
                framesCounter++;
                //10 Segundos
                if (framesCounter > 600)
                {
                    framesCounter = 0;
                    gMngr.SetGhostState(CHASE);
                    pos.x = (roundf((pos.x - offsetX) / tilemap->tileSize)) * tilemap->tileSize + offsetX;
                    pos.y = (roundf((pos.y - offsetY) / tilemap->tileSize)) * tilemap->tileSize + offsetY;
                    movementSpeed = 2;
                    ghostColor = { 255,0,0,255 };
                }
            }

            int posSprite[4] = { 2,1,3,0 };
            bool updateFrame = false;
            switch (direction) {
            case 0:
                pos.y -= movementSpeed;
                updateFrame = true;
                break;
            case 1:
                pos.x -= movementSpeed;
                updateFrame = true;
                break;
            case 2:
                pos.y += movementSpeed;
                updateFrame = true;
                break;
            case 3:
                pos.x += movementSpeed;
                updateFrame = true;
                break;
            }

            if (updateFrame)
            {
                ghostAnimOffset = posSprite[direction];
            }


            if (CheckTileCollision(tilemap, pos, true, gMngr.GetGhostState()))
            {
                pos = oldPos;
            }

            if (CheckCollision(player->GetPos(), pos))
            {
                if (gMngr.GetGhostState() == CHASE && !gMngr.GetDead())
                {
                    //LOSE A LIFE
                    gMngr.SetDead(true);
                    gMngr.DecreaseLives(1);
                }
                else if (gMngr.GetGhostState() == FRIGHTENED)
                {
                    gMngr.SetGhostState(EATEN);
                    direction = setGhostDir(tilemap, pos, direction, movementSpeed, homeTarget);
                    pos.x = (roundf((pos.x - offsetX) / tilemap->tileSize)) * tilemap->tileSize + offsetX;
                    pos.y = (roundf((pos.y - offsetY) / tilemap->tileSize)) * tilemap->tileSize + offsetY;
                    movementSpeed = 4;
                    ghostColor = { 0,128,128,255 };
                    gMngr.IncreaseScore(200);
                    gMngr.GetAudioMngr().PlaySoundEffect(SoundType::EatGhost);
                    if (IsSoundPlaying(gMngr.GetAudioMngr().PowerPill))
                    {
                        StopSound(gMngr.GetAudioMngr().PowerPill);
                    }
                }

            }

        }
    }
}

void Entidad::CheckInput()
{
    if (IsKeyDown(KEY_S))
    {
        if (IsAbleToMove(tilemap, pos, 2, movementSpeed, false, CHASE))
        {
            if (direction != 2)
            {
                direction = 2;
            }
        }
    }
    else if (IsKeyDown(KEY_W))
    {
        if (IsAbleToMove(tilemap, pos, 0, movementSpeed, false, CHASE))
        {
            if (direction != 0)
            {
                direction = 0;
            }
        }
    }

    if (IsKeyDown(KEY_D))
    {
        if (IsAbleToMove(tilemap, pos, 3, movementSpeed, false, CHASE))
        {
            if (direction != 3)
            {
                direction = 3;
            }
        }
    }
    else if (IsKeyDown(KEY_A))
    {
        if (IsAbleToMove(tilemap, pos, 1, movementSpeed, false, CHASE))
        {
            if (direction != 1)
            {
                direction = 1;
            }
        }
    }


    switch (direction) {
    case 0:
        pos.y -= movementSpeed;
        break;
    case 1:
        pos.x -= movementSpeed;
        break;
    case 2:
        pos.y += movementSpeed;
        break;
    case 3:
        pos.x += movementSpeed;
        break;
    }

    if (Entidad::CheckTileCollision(tilemap, pos, false, CHASE))
    {
        pos = oldPos;
    }

}

void Entidad::ValidateGhostCollision()
{

}

void Entidad::ValidatePlayerCollision()
{
    GameManager& gMngr = GameManager::GetGameManager();
    Entidad* ghost = gMngr.GetGhost();

    if (bounds[0] == bounds[2] && bounds[1] == bounds[3])
    {
        int v = (tilemap->objectTiles[bounds[1] * tilemap->tileCountX + bounds[0]].value);
        if (v == 30) {
            tilemap->objectTiles[bounds[1] * tilemap->tileCountX + bounds[0]].value = -1;
            gMngr.IncreaseScore(10);
            gMngr.GetAudioMngr().PlaySoundEffect(SoundType::Waka);
        }
        if (v == 28) {
            
            if (gMngr.GetGhostState() != EATEN)
            {
                gMngr.SetGhostState(FRIGHTENED);
                ghost->SetColor({ 0,0,255,255 });
                ghost->SetDirection(setGhostDir(
                    tilemap, 
                    ghost->GetPos(),
                    ((ghost->GetDirection()+ 2) & 3),
                    ghost->GetSpeed(), frightenedTarget));
                ghost->SetSpeed(1);
                framesCounter = 0;
                gMngr.GetAudioMngr().PlaySoundEffect(SoundType::PowerPill);
            }
            tilemap->objectTiles[bounds[1] * tilemap->tileCountX + bounds[0]].value = -1;
            gMngr.IncreaseScore(50);
        }
        if (v == 28 || v == 30)
        {
            gMngr.IncreaseEatenDots(1);
            if (gMngr.GetEatenDots() >= 218)
            {
                gMngr.ChangeToScreen(GameScreen::ENDING);
                
            }
        }

        if (v != -1)
        {
            printf("Value object Tilemap %d", v);
        }
    }
}

void Entidad::Init(int xPos, int yPos, bool isGhost)
{
    GameManager& gMngr = GameManager::GetGameManager();
    TexturesManager tMngr = gMngr.GetTextMngr();
    tilemap = gMngr.GetTilemap();
    ghostState = gMngr.GetGhostState();
    movementSpeed=2;
    direction=1;
    pos = { xPos * tilemap->tileSize + (float)offsetX, yPos * tilemap->tileSize + (float)offsetY, 32, 32 };
    oldPos = pos;
    animationCounter=0;
    framesSpeed=10;
    currentFrame=0;
    framesCounter=0;
    ghostAnimOffset = 0;
    deadframeCounter = 0;
    isDead = false;
    if (!isGhost)
    {
        frameRec = { 0.0f, (float)texture->height / 4, (float)texture->width / 2, (float)texture->height / 4 };
    }
    else
    {
        frameRec = { (float)texture->height / 4, 0.0f, (float)texture->width / 12, (float)texture->height / 4 };
    }
}

void Entidad::Drawing(bool isGhost)
{
    GameManager& gMngr = GameManager::GetGameManager();
    if (!isGhost)
    {
       DrawTextureRec(*texture, frameRec, {pos.x, pos.y}, WHITE);
       // DrawRectangle(pos.x, pos.y, pos.width, pos.height, {255,255,0,255});
    }
    else
    {
        //DrawRectangle(pos.x, pos.y, pos.width, pos.height, ghostColor);
        DrawTextureRec(*texture, frameRec, { pos.x, pos.y }, WHITE);
    }
}

int Entidad::setGhostDir(Tilemap *tilemap, Rectangle pos, int direction, int speed, int* target)
{
    int resp = 0;
    bool allowDir[4] = { false, false, false, false };
    int ghostPos[4];
    int minDir = 9;
    int minDistance = 9999;

    memcpy(ghostPos, setBounds(tilemap, pos), sizeof(int) * 4);

    if (target[0] < 0 || target[2] < 0 || target[0] >= tilemap->tileCountX || target[2] >= tilemap->tileCountX
        ||
        ghostPos[0] < 0 || ghostPos[2] < 0 || ghostPos[0] >= tilemap->tileCountX || ghostPos[2] >= tilemap->tileCountX)
    {
        resp = direction;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            allowDir[i] = IsAbleToMove(tilemap, pos, i, speed, true, GameManager::GetGameManager().GetGhostState());

            if (((direction + 2) & 3) == i) {
                allowDir[i] = false;
            }

            printf("\nChecking Dir %d %s", i, allowDir[i] ? "ok" : "discard");
            if (allowDir[i])
            {
                memcpy(ghostPos, setBounds(tilemap, pos), sizeof(int) * 4);

                int dist;
                ghostPos[0] += (i == 1 ? -1 : (i == 3 ? 1 : 0));
                ghostPos[1] += (i == 0 ? -1 : (i == 2 ? 1 : 0));
                int dx = target[0] - ghostPos[0];
                int dy = target[1] - ghostPos[1];

                printf("|| (%d,%d,%d,%d) (%d,%d,%d,%d) ", target[0], target[1], target[2], target[3], ghostPos[0], ghostPos[1], ghostPos[2], ghostPos[3]);
                dist = dx * dx + dy * dy;
                printf("|| Distance %d", dist);


                if (dist < minDistance)
                {
                    minDistance = dist;
                    minDir = i;
                }

            }
        }
        if (minDir != 9)
        {
            resp = minDir;
        }
        else
        {
            resp = direction;
        }
    }
    printf("\n Dir 1: (%d), Dir 2: (%d), Dir 3: (%d), Dir 4: (%d)", allowDir[0], allowDir[1], allowDir[2], allowDir[3]);

    printf("\n Resp %d", resp);
    return  resp;
}

int* Entidad::setBounds(Tilemap *tilemap, Rectangle pos)
{
    int bounds[4] =
    {
        floorf((pos.x - offsetX) / tilemap->tileSize),
        floorf((pos.y - offsetY) / tilemap->tileSize),
        floorf(((pos.x - offsetX) + pos.width - 1) / tilemap->tileSize),
        floorf(((pos.y - offsetY) + pos.height - 1) / tilemap->tileSize)
    };
    return bounds;
}

bool Entidad::IsAbleToMove(Tilemap *tilemap, Rectangle pos, int direction, int speed, bool isGhost, BehaviorState ghostState)
{
    bool resp = true;

    float xPos = pos.x - offsetX;
    float yPos = pos.y - offsetY;
    int tileNumber = 0;
    Rectangle projectedPos;

    switch (direction)
    {
    case 0:
        yPos -= speed;
        break;
    case 1:
        xPos -= speed;
        break;
    case 2:
        yPos += speed;
        break;
    case 3:
        xPos += speed;
        break;
    }
    //printf("\n - Trying to move x: %.1f and y: %.1f", xPos, yPos);

    projectedPos = { xPos + offsetX , yPos + offsetY, pos.width, pos.height };
    resp = !CheckTileCollision(tilemap, projectedPos, isGhost, ghostState);
    return resp;
}


bool Entidad::CheckTileCollision(Tilemap *tilemap, Rectangle entity, bool isGhost, BehaviorState ghostState) {
    bool resp = false;
    int tileXMinPos = floorf((entity.x - offsetX) / tilemap->tileSize);
    int tileYMinPos = floorf((entity.y - offsetY) / tilemap->tileSize);
    int tileXMaxPos = floorf((entity.x + entity.width - 1 - offsetX) / tilemap->tileSize);
    int tileYMaxPos = floorf((entity.y + entity.height - 1 - offsetY) / tilemap->tileSize);

    //printf("\n pos (%d,%d) ", tileXMinPos, tileYMinPos);

    int tileNumber[4] =
    {
         tileYMinPos * tilemap->tileCountX + tileXMinPos,
         tileYMaxPos * tilemap->tileCountX + tileXMinPos,
         tileYMinPos * tilemap->tileCountX + tileXMaxPos,
         tileYMaxPos * tilemap->tileCountX + tileXMaxPos
    };

    for (int i = 0; i < 4 && !resp; i++)
    {
        if (!isGhost)
        {
            //printf("\nGhost:%i Collider: %i", isGhost, tilemap->tiles[tileNumber[i]].collider);
            if (tilemap->tiles[tileNumber[i]].collider == 0 || tilemap->tiles[tileNumber[i]].collider == 2)
            {
                resp = true;
            }
        }
        else
        {
            if (ghostState == CHASE || ghostState == FRIGHTENED)
            {
                if (tilemap->tiles[tileNumber[i]].collider == 0 || tilemap->tiles[tileNumber[i]].collider == 2)
                {
                    resp = true;
                }
            }
            else if (ghostState == EATEN)
            {
                if (tilemap->tiles[tileNumber[i]].collider == 0)
                {
                    resp = true;
                }
            }
        }
    }

    if (tileXMinPos < 0 || tileXMaxPos >= tilemap->tileCountX)
    {
        resp = false;
    }

    return resp;
}

bool Entidad::CheckCollision(Rectangle player, Rectangle entity) {
    bool resp = false;
    Rectangle entityCollision = { entity.x + PLAYER_COLLISION_PADDING, entity.y + PLAYER_COLLISION_PADDING, entity.width, entity.height };
    Rectangle playerCollision = { player.x + PLAYER_COLLISION_PADDING, player.y + PLAYER_COLLISION_PADDING, player.width, player.height };
    if (CheckCollisionRecs(playerCollision, entityCollision))
    {
        resp = true;
    }
    return resp;
}

void Entidad::SetTexture(Texture2D* texture)
{
    this->texture = texture;
}

int* Entidad::GetBounds() 
{
    return bounds;
}

int Entidad::GetDirection()
{
    return direction;
}

void Entidad::SetDirection(int dir)
{
    direction = dir;
}

void Entidad::SetSpeed(int speed)
{
    movementSpeed = speed;
}

int Entidad::GetSpeed()
{
    return movementSpeed;
}

Rectangle Entidad::GetPos()
{
    return pos;
}

void Entidad::SetPos(Rectangle pos)
{
    this->pos=pos;
}

void Entidad::SetColor(Color color)
{
    this->ghostColor = color;
}
