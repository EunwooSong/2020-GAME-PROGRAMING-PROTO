#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
	offset = Vec2(SCREEN_WIDTH, SCREEN_HEIGHT) / 2.0f;
}

Scene::~Scene()
{


	for (auto& obj : objList)
		SAFE_DELETE(obj);

	for (auto& ui : uiObjList)
		SAFE_DELETE(ui);
}

void Scene::Render()
{
	Object::Render();

	for (auto& obj : objList)
		obj->Render();

	for (auto& ui : objList)
		ui->Render();
}

void Scene::Update(float dt)
{
	Object::Update(dt);

	for (auto& obj : objList)
		obj->Update(dt);
	for (auto& obj : uiObjList)
		obj->Update(dt);

	FollowTargetMovement(dt);
}

void Scene::AddObject(Object* iter)
{
	objList.push_back(iter);
	AddChild(iter);
	iter->setParent(this);
}

void Scene::RemoveObject(Object* iter)
{
	objList.remove(iter);
	RemoveChild(iter);
}

void Scene::AddUIObject(Object* iter)
{
	uiObjList.push_back(iter);
	iter->setParent(nullptr);
}

void Scene::setFollowTarget(Object* target, float moveSpeed)
{
	this->target = target;
	this->moveSpeed = moveSpeed;
}

Object* Scene::getFollowTarget()
{
	return target;
}

void Scene::setFollowSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

float Scene::getFollowSpeed()
{
	return moveSpeed;
}

void Scene::setMapFrame(Rect mapFrame)
{
	this->mapFrame = mapFrame;
}

void Scene::FollowTargetMovement(float dt)
{
	if (!target) return;

	Vec2 tmpPos = pos;

	tmpPos = Lerp(tmpPos, -(target->getPos() + target->getRect().center() - offset) / scale.x, moveSpeed * dt);
	
	if (tmpPos.x > -mapFrame.left / scale.x) tmpPos.x = -mapFrame.left / scale.x;
	else if (tmpPos.x < -(mapFrame.right - offset.x * 2) / scale.x)
		tmpPos.x = -(mapFrame.right - offset.x * 2) / scale.x;

	if (tmpPos.y > -mapFrame.top / scale.y) tmpPos.y = -mapFrame.top / scale.y;
	else if (tmpPos.y < -(mapFrame.bottom - offset.y * 2) / scale.y)
		tmpPos.y = -(mapFrame.bottom - offset.y * 2) / scale.y;

	pos = tmpPos;
}

Vec2 Scene::ScreenCenter()
{
	return pos + offset;
}