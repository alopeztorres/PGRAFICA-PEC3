#pragma once

class ScrLoading
{
private:
	bool playMusic = false;
public:
	ScrLoading();
	void SetPlayMusic(bool resp) { playMusic = resp; }

	void Init(void);
	void Update(void);
	void Draw(void);
	void Unload(void);
};
