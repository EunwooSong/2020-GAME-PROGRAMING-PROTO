#include "stdafx.h"
#include "Object.h"

Object::Object() :
	pos(0, 0),
	rotationCenter(0, 0),
	scaleCenter(0, 0),
	rotation(0),
	scale(1, 1),
	rect(0, 0, 0, 0),
	visible(true),
	renderChildrenEnable(true),
	parent(nullptr)
{
	D3DXMatrixIdentity(&mat);
}

Object::~Object()
{
	for (auto& child : children)
		SAFE_DELETE(child);
}

void Object::Render()
{
	if (!visible)
		return;

	D3DXMatrixTransformation2D(&mat, &scaleCenter, NULL, &scale, &rotationCenter, rotation, &pos);

	if (parent)
		mat *= parent->mat;

	if (children.size() > 0 && renderChildrenEnable)
		for (auto& child : children)
			child->Render();
}

void Object::Update(float dt)
{
	for (auto& child : children)
		child->Update(dt);
}

void Object::AddChild(Object* iter)
{
	iter->setParent(this);
	children.push_back(iter);
}

void Object::RemoveChild(Object* iter)
{
	children.remove(iter);
	iter->parent = nullptr;
}

bool Object::IsCollisionRect(Vec2 p, Rect r)
{
	//SetMyRect
	Rect myRect = rect.offset(pos);

	//SetTargetRect 
	r.offset(p);

	//Result
	return myRect.Intersects(r);
}

bool Object::IsCollisionRect(Object* obj)
{
	return IsCollisionRect(obj->pos, obj->rect);
}

bool Object::isPointInRect(Vec2 p)
{
	//SetMyRect
	Rect myRect = rect.offset(pos);
	
	//Result
	return myRect.Contain(p);
}

D3DXMATRIX Object::getMat()
{
	return mat;
}

Vec2 Object::getPos()
{
	return pos;
}

int Object::getPosX()
{
	return (int)pos.x;
}

int Object::getPosY()
{
	return (int)pos.y;
}

void Object::setParent(Object* obj)
{
	parent = obj;
}

void Object::setPos(int x, int y)
{
	pos = Vec2(x, y);
}

void Object::setPos(Vec2 pos)
{
	this->pos = pos;
}

Rect Object::getRect()
{
	return rect;
}

void Object::setRect(Rect r)
{
	rect = r;
}

void Object::setVisible(bool visible)
{
	this->visible = visible;
}

bool Object::getVisible()
{
	return visible;
}

void Object::setScale(Vec2 scale)
{
	this->scale = scale;
}

Vec2 Object::getScale()
{
	return scale;
}

void Object::setRenderChildrenEnable(bool enable)
{
	renderChildrenEnable = enable;
}

bool Object::getRenderChildrenEnable()
{
	return renderChildrenEnable;
}
