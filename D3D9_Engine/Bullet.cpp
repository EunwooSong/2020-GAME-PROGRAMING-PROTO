#include "stdafx.h"
#include "Bullet.h"
#include "GameManager.h"
#include "BitMap.h"

Bullet::Bullet(Team team, Vec2 moveDir, float damage, float speed)
	: team(team), moveDir(moveDir), damage(damage), speed(speed), isHit(false)
{
	bullet = new Animation(1);
	bullet->AddFrame("Resources/Image/Bullet/Player/shot-1.png");
	AddChild(bullet);
}

Bullet::~Bullet()
{
}

void Bullet::Update(float dt)
{
	Object::Update(dt);

	pos += moveDir * speed * dt;

	if (bitMap.getBit((int)pos.x, (int)pos.y) == M_WALL) {
		GAME_MGR.inGame->CreateEffect(E_BULLET, this->pos);
		isHit = true;
	}
}

bool Bullet::getIsHitBullet()
{
	return isHit;
}
