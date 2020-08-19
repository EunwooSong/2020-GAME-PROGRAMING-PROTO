#pragma once
#include "Define.h"
#include "Texture.h"

#define LAYER_GROUND 0
#define LAYER_COUNT 1

class BitMap
{
private:
	MapCollision*** bits ;
	int width = 0;
	int height = 0;

public:
	BitMap();
	~BitMap();
	void init(UINT width, UINT height);
	void dispose();
	void AddTile(int x, int y, string uri, int layer = LAYER_GROUND);
	void setBit(int x, int y, bool b, int layer = LAYER_GROUND);
	void setBit(int x, int y, D3DCOLOR type, int layer = LAYER_GROUND);
	MapCollision getBit(int x, int y, int layer = LAYER_GROUND);
};

extern BitMap bitMap;