#pragma once

class ScrEnding
{
private:
	bool playMusic = false;
public:
	ScrEnding();
	void SetPlayMusic(bool resp) { playMusic=resp; }

	void Init(void);
	void Update(void);
	void Draw(void);
	void Unload(void);
};
