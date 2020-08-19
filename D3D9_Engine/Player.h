#pragma once
#include "Unit.h"
class Player :
    public Unit
{
private:
    Animation* anim_idle = nullptr;
    Animation* anim_run = nullptr;
    Animation* anim_jumpUp = nullptr;
    Animation* anim_jumping = nullptr;
    Animation* anim_duck = nullptr;
    Animation* anim_runShot = nullptr;
    Animation* anim_idleShot = nullptr;

    float currentSpeed;
    float decSpeed;
    Vec2 moveDir;
    bool isHit;
    float jumpPower;
    float currentYPower;
    bool isJump;
    float gravity;
    float groundLength;
    bool isGround;
    bool isShoot;
    bool isMove;
    bool isDeathZone;
    bool isDie;
    Vec2 checkPos;

    bool skill_1_used;
    float skill_1_timer;
    float skill_1_particle_timer;

    float particleTimer;

    void AddAnimationFrame();
public:
    Player(float moveSpeed, float jumpPower, float damage);
    ~Player();
    void Update(float dt);
    void CheckGround();     
    void Movement(float dt);
    void AnimationController();
    void SwapAnimation(Animation * iter);
    void setCheckPoint(Vec2 pos);
    void ReturnCheckPoint();
    bool CheckDeathZone();
};

