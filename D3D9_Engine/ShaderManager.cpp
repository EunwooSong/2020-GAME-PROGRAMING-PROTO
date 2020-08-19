#include "stdafx.h"
#include "ShaderManager.h"

void ShaderManager::Dispose()
{
	for (auto shader : shaderList)
		SAFE_RELEASE(shader.second);
}

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	Dispose();
}

LPD3DXEFFECT ShaderManager::LoadShaderFromFile(const char* path)
{
	if (shaderList[path] == NULL) {
		D3DXCreateEffectFromFileA(
			pd3dDevice,
			path,
			NULL,
			NULL,
			D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,
			NULL,
			&shaderList[path],
			NULL
		);
	}

	return shaderList[path];
}
