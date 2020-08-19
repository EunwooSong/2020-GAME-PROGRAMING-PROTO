#include "stdafx.h"
#include "TestScene.h"
#include "BitMap.h"
#include "Player.h"

TestScene::TestScene()
{
	bg = new Sprite("Resources/Image/Stage/1/stage_1_bg.png");
	AddChild(bg);

	wall = new Sprite("Resources/Image/Stage/1/stage_1_wall.png");
	AddChild(wall);

	bitMap.init(3000, 3000);
	bitMap.AddTile(0,0,"Resources/Image/Stage/1/stage_1_collision.png");

	//scale = Vec2(3, 3);
	//tmp = new Sprite("Resources/Image/Player/player-idle/0.png");
	//tmp->setRect(Rect(100, 100));
	tmp = new Player(235, 400, 10);
	tmp->setPos(255, 320);
	AddChild(tmp);

	setFollowTarget(tmp);
	setMapFrame(wall->getRect());

	cout << "Done!" << endl;
}

TestScene::~TestScene()
{
}

void TestScene::Update(float dt)
{
	Scene::Update(dt);

	/*if (inputManager->GetKeyState('W') == kEY_ON)
		tmp->setPos(tmp->getPos() + Vec2(0, -1) * dt * 100);
	if (inputManager->GetKeyState('A') == kEY_ON)
		tmp->setPos(tmp->getPos() + Vec2(-1, 0) * dt * 100);
	if (inputManager->GetKeyState('S') == kEY_ON)
		tmp->setPos(tmp->getPos() + Vec2(0, 1) * dt * 100);
	if (inputManager->GetKeyState('D') == kEY_ON)
		tmp->setPos(tmp->getPos() + Vec2(1, 0) * dt * 100);*/

	//cout << "target : " << (int)target->getPos().x << ", " << (int)target->getPos().y << endl;
}

void TestScene::Render()
{
	Scene::Render();

	/*if (inputManager->GetKeyState(VK_LBUTTON) == KEY_DOWN) {
		switch (bitMap.getBit((int)inputManager->GetMousePos().x, (int)inputManager->GetMousePos().y)) {
		case M_NONE: cout << "M_NONE" << endl; break;
		case M_WALL: cout << "M_WALL" << endl; break;
		case M_DEATH: cout << "M_DEATH" << endl; break;
		case M_CLEAR: cout << "M_CLEAR" << endl; break;
		case M_OUT_MAP: cout << "M_OUT_MAP" << endl; break;
		}
	}*/
}
