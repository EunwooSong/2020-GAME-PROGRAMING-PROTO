#include "stdafx.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

LPDIRECT3DTEXTURE9 TextureManager::LoadTextureFromFile(const char* path)
{
	/*if (!std::experimental::filesystem::v1::exists(path))
		cout << "파일 없음 : " << path << endl;*/

	if (textureMap[path] == NULL) {
		D3DXCreateTextureFromFileExA(
			pd3dDevice,
			path,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			NULL,
			NULL,
			NULL,
			&textureMap[path]
			);
	}

	return textureMap[path];
}
