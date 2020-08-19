#include "stdafx.h"
#include "GameScene.h"
#include "GameManager.h"
#include "BitMap.h"

GameScene::GameScene() : returnTimer(0.0f), isDeath(false)
{
    GAME_MGR.inGame = this;

    bg = new Sprite("Resources/Image/Stage/1/stage_1_bg.png");
    AddChild(bg);

    wall = new Sprite("Resources/Image/Stage/1/stage_1_wall.png");
    AddChild(wall);

    bitMap.init(3000, 3000);
    bitMap.AddTile(0, 0, "Resources/Image/Stage/1/stage_1_collision.png");
    soundManager->LoadWaveFile("Resources/Sound/Ingame.wav", "BGM");
    soundManager->PlayWaveFile("BGM");

    //scale = Vec2(3, 3);
    //tmp = new Sprite("Resources/Image/Player/player-idle/0.png");
    //tmp->setRect(Rect(100, 100));
    player = new Player(235, 400, 10);
    player->setPos(255, 320);
    player->setCheckPoint(Vec2(255, 320));
    AddChild(player);

    setFollowTarget(player);
    setMapFrame(wall->getRect());

    cout << "Done!" << endl;
}

GameScene::~GameScene()
{
}

void GameScene::Update(float dt)
{
    Scene::Update(dt);

    for (auto iter = particleList.begin(); iter != particleList.end(); iter++) {
        if ((*iter)->getIsEnd()) {
            RemoveChild((*iter));
            iter = particleList.erase(iter);
            if (iter == particleList.end())
                break;
        }
    }
    for (auto iter = effectList.begin(); iter != effectList.end(); iter++) {
        if ((*iter)->getIsEnd()) {
            RemoveChild((*iter));
            iter = effectList.erase(iter);
            if (iter == effectList.end())
                break;
        }
    }
    for (auto iter = bulletList.begin(); iter != bulletList.end(); iter++) {
        if ((*iter)->getIsHitBullet()) {
            RemoveChild((*iter));
            iter = bulletList.erase(iter);
            if (iter == bulletList.end())
                break;
        }
    }

    //플레이어 죽음 처리
    if (player->CheckDeathZone() && !isDeath) {
        cout << "DeathZone" << endl;
        isDeath = true;
        player->setVisible(false);
        CreateEffect(E_EXPLOSION, player->getPos()
            + Vec2(0, player->getRect().height()));
    }
    
    if (isDeath) {
        returnTimer += dt;

        if (returnTimer > 1.0f) {
            player->ReturnCheckPoint();
            isDeath = false;
            returnTimer = 0.0f;
            player->setVisible(true);
        }
    }
}

void GameScene::Render()
{
    Scene::Render();
}

Particle* GameScene::CreateParticle(ParticleType type, Vec2 pos, LPDIRECT3DTEXTURE9 t)
{
    Particle* tmp = new Particle(t, type);
    tmp->setPos(pos);
    AddChild(tmp);
    particleList.push_back(tmp);
    return tmp;
}

Animation* GameScene::CreateEffect(EffectType type, Vec2 pos)
{
    Animation* iter = nullptr;

    switch (type)
    {
    case E_BULLET:
        iter = new Animation(3);
        iter->AddFrame("Resources/Image/Effect/p_bullet/shot-2.png");
        break;
    case E_EXPLOSION:
        iter = new Animation(10);
        iter->AddFrame("Resources/Image/Effect/death/0.png");
        iter->AddFrame("Resources/Image/Effect/death/1.png");
        iter->AddFrame("Resources/Image/Effect/death/2.png");
        iter->AddFrame("Resources/Image/Effect/death/3.png");
        iter->AddFrame("Resources/Image/Effect/death/4.png");
        break;
    default:
        break;
    }
    if(iter) iter->setPos(pos - iter->getRect().center());
    AddChild(iter);
    effectList.push_back(iter);
    return iter;
}

Bullet* GameScene::CreateBullet(BulletType type, Team team, Vec2 pos, Vec2 moveDir, float damage, float speed)
{
    Bullet* bullet = new Bullet(team, moveDir, damage, speed);
    bullet->setPos(pos);
    AddChild(bullet);
    bulletList.push_back(bullet);
    return bullet;
}
