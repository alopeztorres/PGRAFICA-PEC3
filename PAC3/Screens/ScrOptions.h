#pragma once

class GameManager;

class ScrOptions
{
	GameManager* gm;
public:
	ScrOptions();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Unload(void);
};
