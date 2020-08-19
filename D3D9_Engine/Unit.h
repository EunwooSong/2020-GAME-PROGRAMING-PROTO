#pragma once
#include "Object.h"
#include "Animation.h"

class Unit :
    public Object
{
protected:
    Team team;
    UnitType type;
    int hp_origin;
    int hp;
    pair<float, float> fire_delay;
    float speed;
    float color_r;
    int damage;
    bool isDie;

    Rect hitbox;

    Animation* currentAnim;

public:
    Unit(Team team, UnitType type, int hp_origin, float fire_delay, int speed, int damage);
    ~Unit();

    void Update(float dt);
    virtual void hit(float damage);
    Rect getHitBox();
    Rect getHitWithPos();
};

