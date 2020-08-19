#include "stdafx.h"
#include "BitMap.h"
#include "TextureManager.h"

BitMap::BitMap()
{
}

BitMap::~BitMap()
{
	dispose();
}

void BitMap::init(UINT width, UINT height)
{
	this->width = width;
	this->height = height;

	bits = new MapCollision** [LAYER_COUNT];

	//Create BitMap
	for (int z = 0; z < LAYER_COUNT; z++) {
		bits[z] = new MapCollision * [height];

		for (int y = 0; y < height; y++) {
			bits[z][y] = new MapCollision[width];

			for (int x = 0; x < width; x++)
				bits[z][y][x] = M_NONE;
		}
	}
}

void BitMap::dispose()
{
	//Dispose BitMap
	for (int z = 0; z < LAYER_COUNT; z++) {
		for (int y = 0; y < height; y++)
			SAFE_DELETE(bits[z][y]);
		SAFE_DELETE(bits[z]);
	}
}

void BitMap::AddTile(int x, int y, string uri, int layer)
{
	LPDIRECT3DTEXTURE9 srcTex = textureManager->LoadTextureFromFile(uri.c_str());

	D3DSURFACE_DESC desc;
	srcTex->GetLevelDesc(0, &desc);

	int width = desc.Width;
	int height = desc.Height;

	D3DLOCKED_RECT rect;
	ZeroMemory(&rect, sizeof(rect));
	srcTex->LockRect(0, &rect, 0, 0);
	const BYTE* pSrcTex = static_cast<BYTE*>(rect.pBits);

	for (int y = 0; y < (int)height; y++) {
		for (int x = 0; x < (int)width; x++) {
			int index = x * 4 + y * (width * 4);
			const BYTE* pSrcColor = &pSrcTex[index];
			BYTE alpha = pSrcColor[3];

			if (alpha == 0xff) {
				setBit(x, y, D3DCOLOR_RGBA(
					pSrcColor[0],
					pSrcColor[1],
					pSrcColor[2],
					pSrcColor[3]),
					layer);
			}
		}
	}
}

void BitMap::setBit(int x, int y, bool b, int layer)
{
	if (x != Clamp(x, width, 0)) return;
	if (y != Clamp(y, height, 0)) return;

	bits[layer][y][x] = M_WALL;
}

void BitMap::setBit(int x, int y, D3DCOLOR type, int layer)
{
	MapCollision collision = M_NONE;



	switch (type)
	{
	case D3DCOLOR_RGBA(255, 255, 255, 255): collision = M_WALL; break;
	case D3DCOLOR_RGBA(42, 0, 255, 255): collision = M_DEATH; break;
	case D3DCOLOR_RGBA(0, 140, 16, 255): collision = M_CLEAR; break;
	case D3DCOLOR_RGBA(0, 0, 0, 255):collision = M_NONE; break;
	}

	bits[layer][y][x] = collision;
}



MapCollision BitMap::getBit(int x, int y, int layer)
{
	if (x != Clamp(x, width, 0)) return M_OUT_MAP;
	if (y != Clamp(y, height, 0)) return M_OUT_MAP;

	return bits[layer][y][x];
}

BitMap bitMap;