#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	: currentScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	SAFE_DELETE(currentScene);
}

void SceneManager::Render()
{
	currentScene->Render();
}

void SceneManager::Update(float dTime)
{
	currentScene->Update(dTime);
}

void SceneManager::ChangeScene(Scene* iter)
{
	if (currentScene) SAFE_DELETE(currentScene);
	currentScene = iter;
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}
