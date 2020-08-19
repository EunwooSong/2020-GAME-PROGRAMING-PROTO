#include "stdafx.h"
#include "Unit.h"

Unit::Unit(Team team, UnitType type, int hp_origin, float fire_delay, int speed, int damage)
	: team(team), type(type), hp_origin(hp_origin), hp(hp_origin),
	fire_delay(0, fire_delay), speed(speed), damage(damage),
	color_r(1.0f), isDie(false)
{
}

Unit::~Unit()
{
}

void Unit::Update(float dt)
{
	Object::Update(dt);
	color_r = Clamp(color_r + dt, 1.0f, 0.0f);

	fire_delay.first += dt;

	if (currentAnim) {
		D3DXCOLOR tmp_c = currentAnim->getColor();
		tmp_c.g = tmp_c.b = color_r;
		currentAnim->setColor_ARGB(tmp_c);
	}
}

void Unit::hit(float damage)
{
	hp -= damage;

	color_r = 0.5f;

	if (hp < 0.0f) {
		hp = 0.0f;
		isDie = true;
	}
}

Rect Unit::getHitBox()
{
	return hitbox;
}

Rect Unit::getHitWithPos()
{
	return hitbox.offset(pos);
}
