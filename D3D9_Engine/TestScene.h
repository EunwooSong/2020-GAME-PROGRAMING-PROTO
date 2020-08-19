#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Player.h"

class TestScene :
    public Scene
{
private:
    Sprite* bg;
    Sprite* wall;
    Object* tmp;
    list<Rect> bg_rect;

    //Rect�� ���� �߰�����

public:
    TestScene();
    ~TestScene();

    void Update(float dt);
    void Render();
};