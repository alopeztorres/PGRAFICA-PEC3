#pragma once
#include "raylib.h"
#include "GlobalDefines.h"


class Entidad {
public:
	Entidad();
	void Init(int xPos, int yPos, bool isGhost);
	void Update(bool isGhost);
	void Drawing(bool isGhost);
		
	void CheckInput();
	void SetTexture(Texture2D* texture);
	int* GetBounds();
	int GetDirection();
	void SetDirection(int dir);
	void ValidatePlayerCollision();
	void ValidateGhostCollision();
	Rectangle GetPos();
	void SetPos(Rectangle pos);
	void SetSpeed(int speed);
	void SetColor(Color color);
	int GetSpeed();


	bool IsAbleToMove(Tilemap* tilemap, Rectangle pos, int direction, int speed, bool isGhost, BehaviorState ghostState);
	int* setBounds(Tilemap* tilemap, Rectangle pos);
	bool CheckTileCollision(Tilemap* tilemap, Rectangle entity, bool isGhost, BehaviorState ghostState);
	int setGhostDir(Tilemap* tilemap, Rectangle pos, int direction, int speed, int* playerBound);
	bool CheckCollision(Rectangle player, Rectangle entity);

	bool IsDead() { return isDead; }
	void SetDead(bool resp) { isDead=resp; }

private:
	int direction; //0up 1left 2down 3right
	int movementSpeed;
	int bounds[4] = { 0,0,0,0 };
	int oldBounds[4] = { 0,0,0,0 };
	int animationCounter;
	int framesCounter;
	int deadframeCounter;
	int framesSpeed;
	int currentFrame;
	int ghostAnimOffset;
	BehaviorState ghostState;
	Rectangle pos;
	Rectangle oldPos;
	Tilemap* tilemap;
	Tilemap* tilemapObjects;
	Rectangle frameRec;
	Texture2D* texture;
	int frightenedTarget[4] = { 24,-2,24,-2 };
	int homeTarget[4] = { 13,11,13,11 };
	int exitTarget[4] = { 13,9,13,11 };
	Color ghostColor = { 255,0,0,255 };
	bool isDead;
};