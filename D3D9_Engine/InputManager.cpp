#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager()
{
	ZeroMemory(currentKeys, sizeof(currentKeys));
	ZeroMemory(beforeKeys, sizeof(beforeKeys));
}

InputManager::~InputManager()
{
}

void InputManager::UpdateKeyState()
{
	for (int i = 0; i < 256; i++) {
		beforeKeys[i] = currentKeys[i];
		currentKeys[i] = GetAsyncKeyState(i) & 0x8000;
	}

	GetCursorPos(&cursorPos);
	ScreenToClient(hWnd, &cursorPos);
}

int InputManager::GetKeyState(int vk)
{
	if (beforeKeys[vk] && currentKeys[vk]) return kEY_ON;
	else if (!beforeKeys[vk] && currentKeys[vk]) return KEY_DOWN;
	else if (beforeKeys[vk] && !currentKeys[vk]) return KEY_UP;
	else return KEY_NONE;
}

Vec2 InputManager::GetMousePos()
{
	return Vec2(cursorPos.x, cursorPos.y);
}

Vec2 InputManager::GetWorldMousePos()
{
	return GetMousePos() - Vec2(SCREEN_WIDTH, SCREEN_HEIGHT) / 2.0f
		+ sceneManager->getCurrentScene()->ScreenCenter();
}
