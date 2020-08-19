#pragma once
#include "Define.h"

class Object
{
protected:
	Object* parent;
	D3DXMATRIX mat;
	Vec2 pos;
	Vec2 scaleCenter;
	Vec2 scale;
	Vec2 rotationCenter;
	float rotation;
	Rect rect;
	bool visible;
	bool renderChildrenEnable;
	std::list<Object*> children;

public:
	Object();
	~Object();

	virtual void Render();
	virtual void Update(float dt);

	void AddChild(Object* iter);
	void RemoveChild(Object* iter);

	bool IsCollisionRect(Vec2 p, Rect r);
	bool IsCollisionRect(Object* obj);
	bool isPointInRect(Vec2 p);

	D3DXMATRIX getMat();
	Vec2 getPos();

	int getPosX();
	int getPosY();

	void setParent(Object* obj);

	void setPos(int x, int y);
	void setPos(Vec2 pos);

	Rect getRect();
	void setRect(Rect r);

	void setVisible(bool visible);
	bool getVisible();

	void setScale(Vec2 scale);
	Vec2 getScale();

	void setRenderChildrenEnable(bool enable);
	bool getRenderChildrenEnable();
};

