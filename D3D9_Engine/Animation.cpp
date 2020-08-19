#include "stdafx.h"
#include "Animation.h"
#include <string>

Animation::Animation(int fps)
	: fps(fps),
	color(D3DCOLOR_ARGB(255, 255, 255, 255)),
	maxFrame(0),
	currentFrame(0),
	timeChecker(0),
	height(0),
	width(0),
	isEnd(false),
	isLoop(true),
	isLoopEnd(false)
{
	setRenderChildrenEnable(false);
}

Animation::~Animation()
{
	for (auto& iter : spriteVector)
		SAFE_DELETE(iter);
}

void Animation::Render()
{
	if (!visible) return;
	Object::Render();

	if (maxFrame > 0) {
		spriteVector[currentFrame]->setColor(color);
		spriteVector[currentFrame]->Render();
	}
}

void Animation::Update(float dt)
{
	timeChecker += dt;

	if (isLoopEnd)
		isLoopEnd = false;


	if (timeChecker > 1.0f / fps) {
		timeChecker = 0;
		currentFrame++;

		if (currentFrame == maxFrame) {
			if (isLoop) {
				currentFrame = 0;
				isLoopEnd = true;
			}
			else {
				currentFrame = maxFrame - 1;
				isEnd = true;
			}
		}
	}
}

void Animation::AddFrame(const char* path)
{
	spriteVector.push_back(new Sprite(path));
	AddChild(spriteVector[maxFrame]);

	if (maxFrame == 0) {
		width = spriteVector[maxFrame]->getWidth();
		height = spriteVector[maxFrame]->getHeight();
		rect = Rect(0, 0, width, height);
	}

	maxFrame++;
}

void Animation::AddFrame(string path, int count)
{
	for (int i = 0; i < count; i++) {
		string p = path + "/" + to_string(i) + ".png";
		spriteVector.push_back(new Sprite(p.c_str()));
		AddChild(spriteVector[maxFrame]);

		maxFrame++;
	}

	rect = spriteVector[0]->getRect();
}

void Animation::setLoop(bool isLoop)
{
	this->isLoop = isLoop;
}

bool Animation::getIsEnd()
{
	return isEnd || isLoopEnd;
}

void Animation::RestartAnimation()
{
	currentFrame = 0;
	timeChecker = 0;
	isLoopEnd = false;
	isEnd = false;
}

void Animation::setColor_A(float a)
{
	color.a = a;
}

void Animation::setColor_R(float r)
{
	color.r = r;
}

void Animation::setColor_G(float g)
{
	color.g = g;
}

void Animation::setColor_B(float b)
{
	color.b = b;
}

void Animation::setColor_ARGB(D3DXCOLOR color)
{
	this->color = color;
}

D3DXCOLOR Animation::getColor()
{
	return color;
}

LPDIRECT3DTEXTURE9 Animation::getCurrentTexture()
{
	return spriteVector[currentFrame]->getTexture();
}