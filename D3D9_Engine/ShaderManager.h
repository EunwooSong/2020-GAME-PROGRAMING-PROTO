#pragma once
#include "Define.h"

class ShaderManager
{
private:
	map<const char*, LPD3DXEFFECT> shaderList;
	void Dispose();
public:
	ShaderManager();
	~ShaderManager();
	LPD3DXEFFECT LoadShaderFromFile(const char* path);
};