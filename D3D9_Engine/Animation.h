#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Sprite.h"

class Animation :
	public Object
{
private:
	int height;
	int width;
	int maxFrame;
	int currentFrame;
	int fps;

	bool isEnd;
	bool isLoop;
	bool isLoopEnd;

	D3DXCOLOR color;
	float timeChecker;

	std::vector<Sprite*> spriteVector;

public:

	Animation(int fps);
	~Animation();

	void Render();
	void Update(float dt);

	void AddFrame(const char * path);
	void AddFrame(string path, int count);

	void setLoop(bool isLoop);
	bool getIsEnd();

	void RestartAnimation();

	void setColor_A(float a);
	void setColor_R(float r);
	void setColor_G(float g);
	void setColor_B(float b);
	void setColor_ARGB(D3DXCOLOR color);
	D3DXCOLOR getColor();

	LPDIRECT3DTEXTURE9 getCurrentTexture();
};

