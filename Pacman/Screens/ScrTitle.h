#pragma once

class ScrTitle
{
private:
	Vector2 position;
	Texture2D* texture;

public:
	ScrTitle();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Unload(void);
};
