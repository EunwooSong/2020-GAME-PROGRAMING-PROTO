#pragma once
#include "Object.h"

class Scene
	: public Object
{
protected:
	std::list<Object*> objList;
	std::list<Object*> uiObjList;
	Object* target = nullptr;

	Vec2 offset;
	Rect mapFrame;

	float moveSpeed;

public:
	Scene();
	~Scene();

	void Render();
	void Update(float dt);

	void AddObject(Object* iter);
	void RemoveObject(Object* iter);
	void AddUIObject(Object* iter);

	void setFollowTarget(Object* target, float moveSpeed = 5.0f);
	Object * getFollowTarget();
	void setFollowSpeed(float moveSpeed = 5.0f);
	float getFollowSpeed();

	void setMapFrame(Rect mapFrame);

	void FollowTargetMovement(float dt);
	Vec2 ScreenCenter();
};

