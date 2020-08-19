#pragma once
#include "Scene.h"
#include "Particle.h"
#include "Bullet.h"
#include "Player.h"

class GameScene :
    public Scene
{
public:
    list<Particle*> particleList;
    list<Animation*> effectList;
    list<Bullet*> bulletList;

    Sprite* bg;
    Sprite* wall;
    Player* player;

    float returnTimer;
    bool isDeath;

public:
    GameScene();
    ~GameScene();

    void Update(float dt);
    void Render();

    Particle* CreateParticle(ParticleType type, Vec2 pos, LPDIRECT3DTEXTURE9 t = nullptr);
    Animation* CreateEffect(EffectType type, Vec2 pos);
    Bullet* CreateBullet(BulletType type, Team team , Vec2 pos, Vec2 moveDir, float damage, float speed);
};