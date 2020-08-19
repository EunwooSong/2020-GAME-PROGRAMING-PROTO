#pragma once
#include "Object.h"
#include "Animation.h"

class Bullet :
    public Object
{
private:
    Team team;
    Animation* bullet;
    float damage;
    float speed;
    bool isHit;
    Vec2 moveDir;

public:
    Bullet(Team team, Vec2 moveDir, float damage, float speed);
    ~Bullet();

    void Update(float dt);
    bool getIsHitBullet();
};

