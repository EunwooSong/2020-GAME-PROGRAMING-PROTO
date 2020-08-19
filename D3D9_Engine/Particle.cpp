#include "stdafx.h"
#include "Particle.h"

Particle::Particle(string p, ParticleType type, float fadeSpeed, float moveSpeed, float targetAngle)
	: Sprite(p.c_str()), type(type), fadeSpeed(fadeSpeed), moveSpeed(moveSpeed),
	targetAngle(targetAngle), isFadeIn(false),isEnd(true), moveDecSpeed(100), isMove(true),
	target(nullptr)
{
	if (type == P_FADE_IN || type == P_FADE_IN_OUT) {
		color.a = 0.0f;
		isFadeIn = true;
	}

	scaleCenter = rect.center();
}

Particle::Particle(LPDIRECT3DTEXTURE9 p, ParticleType type, float fadeSpeed, float moveSpeed, float targetAngle)
	: Sprite(p), type(type), fadeSpeed(fadeSpeed), moveSpeed(moveSpeed),
	targetAngle(targetAngle), isFadeIn(false), isEnd(false), moveDecSpeed(100), isMove(true),
	target(nullptr)
{
	if (type == P_FADE_IN || type == P_FADE_IN_OUT) {
		color.a = 0.0f;
		isFadeIn = true;
	}
}

Particle::~Particle()
{
}

void Particle::Update(float dt)
{
	if (isEnd) return;

	switch (type)
	{
	case P_FADE_IN:
		color.a += fadeSpeed * dt;

		if (color.a > 1.0f)
			isEnd = true;
		break;
	case P_FADE_OUT:
		color.a -= fadeSpeed * dt;

		if (color.a < 0.0f)
			isEnd = true;
		break;
	case P_FADE_IN_OUT:
		if (isFadeIn)
			color.a += fadeSpeed * dt;
		else
			color.a -= fadeSpeed * dt;

		if (color.a > 1.0f)
			isFadeIn = false;

		if (!isFadeIn && color.a < 0.0f)
			isEnd = true;
		break;
	case P_MOVE_RIT:
		color.a -= fadeSpeed * dt;

		if (color.a < 0.0f)
			isEnd = true;

		pos += Vec2(cos(targetAngle), sin(targetAngle)) * moveSpeed * dt;
		moveSpeed -= fadeSpeed * dt;
		break;
	case P_COIN:
		if (isMove) {
			moveSpeed -= moveDecSpeed * dt;

			pos += Vec2(cos(targetAngle), sin(targetAngle)) * moveSpeed * dt;

			if (moveSpeed < 0.0f) {
				moveSpeed = 1000.0f;
				isMove = false;
			}
		}
		else {
			targetAngle = Angle(this->pos, target->getPos());

			pos += Vec2(cos(targetAngle), sin(targetAngle)) * moveSpeed * dt;
		}
		break;
	default:
		break;
	}
}

void Particle::setMoveDecSpeed(float speed)
{
	moveDecSpeed = speed;
}

void Particle::setTargetAngle(float targetAngle)
{
	this->targetAngle = targetAngle;
}

void Particle::setMoveSpeed(float speed)
{
	moveSpeed = speed;
}

void Particle::setTarget(Object* target)
{
	this->target = target;
}

bool Particle::getIsEnd()
{
	return isEnd;
}


