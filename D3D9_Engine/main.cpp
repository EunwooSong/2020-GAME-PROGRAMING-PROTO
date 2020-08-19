#include "stdafx.h"
#include "Console.h"
#include "Application.h"
#include "TestScene.h"
#include "GameScene.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, INT cmdShow) {
	srand(GetTickCount());

	Console console;
	Application app;

	if (CONSOLE_ON) {
		console.OpenConsole();
	}

	app.InitWindow(hInstance);
	app.InitD3D(app.FloatWindow(hInstance, cmdShow));
	app.InitManager();

	return app.DoMainLoop(new GameScene());
}