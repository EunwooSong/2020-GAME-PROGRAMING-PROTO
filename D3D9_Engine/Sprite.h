#pragma once
#include "Object.h"
#include "Texture.h"

class Sprite :
	public Object
{
protected:
	LPDIRECT3DTEXTURE9 texture;
	D3DXCOLOR color;
	Rect visibleRect;
	int width;
	int height;

public:
	Sprite(const char* path);
	Sprite(LPDIRECT3DTEXTURE9 texture);
	~Sprite();

	void Render();

	int getWidth();
	int getHeight();
	D3DCOLOR getColor();

	void setColor(D3DCOLOR color);
	void setCenter();
	void setScaleCenter(D3DXVECTOR2 p);

	LPDIRECT3DTEXTURE9 getTexture();
};

