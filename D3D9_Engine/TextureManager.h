#pragma once
#include "Define.h"
#include "Texture.h"

class TextureManager
{
private:
	std::map<const char *, LPDIRECT3DTEXTURE9> textureMap;

public:
	TextureManager();
	~TextureManager();

	LPDIRECT3DTEXTURE9 LoadTextureFromFile(const char* path);
};

