#pragma once
#include "Define.h"

class Texture
{
public:
	LPDIRECT3DTEXTURE9 d3dTexture;
	D3DXIMAGE_INFO info;

public:
	Texture();
	~Texture();
};

