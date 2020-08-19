#pragma once
#include "GameScene.h"

class GameManager
{
public:
	GameManager() {};
	~GameManager() {};
	GameScene* inGame = nullptr;
};

extern GameManager GAME_MGR;