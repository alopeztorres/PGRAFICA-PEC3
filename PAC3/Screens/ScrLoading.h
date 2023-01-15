#pragma once

class GameManager;

class ScrLoading
{
private:
	bool playMusic = false;
	bool loading = false;
	int framesCounter = 0;
	GameManager *gm;
public:
	ScrLoading();
	void SetPlayMusic(bool resp) { playMusic = resp; }
	void Reload();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Unload(void);
};
