#include "stdafx.h"
#include "Player.h"
#include "BitMap.h"
#include "GameManager.h"

Player::Player(float moveSpeed, float jumpPower, float damage)
	: Unit(PLAYER, U_PLAYER, 100, 0.3f, moveSpeed, damage),
	decSpeed(moveSpeed), currentSpeed(0), moveDir(1, 0), isHit(false),
	jumpPower(jumpPower), currentYPower(0), gravity(9.81f), groundLength(5),
	isGround(false), isJump(false), isShoot(false), isMove(false),
	skill_1_timer(0.0f), skill_1_used(false), particleTimer(0.0f), isDie(false),
	skill_1_particle_timer(0.0f)
{
	anim_idle = new Animation(10);
	anim_run = new Animation(17);
	anim_duck = new Animation(30);
	anim_runShot = new Animation(17);
	anim_idleShot = new Animation(10);
	anim_jumpUp = new Animation(1);
	anim_jumping = new Animation(12);

	AddAnimationFrame();

	rect = hitbox = Rect(-30, 0, 30,120);
	currentYPower = -300;
	//scaleCenter = rect.center();
}

Player::~Player()
{
}

void Player::AddAnimationFrame()
{
	anim_idle->AddFrame("Resources/Image/Player/player-idle/0.png");
	anim_idle->AddFrame("Resources/Image/Player/player-idle/1.png");
	anim_idle->AddFrame("Resources/Image/Player/player-idle/2.png");
	anim_idle->AddFrame("Resources/Image/Player/player-idle/3.png");

	anim_run->AddFrame("Resources/Image/Player/player-run/0.png");
	anim_run->AddFrame("Resources/Image/Player/player-run/1.png");
	anim_run->AddFrame("Resources/Image/Player/player-run/2.png");
	anim_run->AddFrame("Resources/Image/Player/player-run/3.png");
	anim_run->AddFrame("Resources/Image/Player/player-run/4.png");
	anim_run->AddFrame("Resources/Image/Player/player-run/5.png");
	anim_run->AddFrame("Resources/Image/Player/player-run/6.png");
	anim_run->AddFrame("Resources/Image/Player/player-run/7.png");
	anim_run->AddFrame("Resources/Image/Player/player-run/8.png");
	anim_run->AddFrame("Resources/Image/Player/player-run/9.png");

	anim_duck->AddFrame("Resources/Image/Player/player-duck", 1);
	anim_runShot->AddFrame("Resources/Image/Player/player-run-shot/0.png");
	anim_runShot->AddFrame("Resources/Image/Player/player-run-shot/1.png");
	anim_runShot->AddFrame("Resources/Image/Player/player-run-shot/2.png");
	anim_runShot->AddFrame("Resources/Image/Player/player-run-shot/3.png");
	anim_runShot->AddFrame("Resources/Image/Player/player-run-shot/4.png");
	anim_runShot->AddFrame("Resources/Image/Player/player-run-shot/5.png");
	anim_runShot->AddFrame("Resources/Image/Player/player-run-shot/6.png");
	anim_runShot->AddFrame("Resources/Image/Player/player-run-shot/7.png");
	anim_runShot->AddFrame("Resources/Image/Player/player-run-shot/8.png");
	anim_runShot->AddFrame("Resources/Image/Player/player-run-shot/9.png");

	anim_idleShot->AddFrame("Resources/Image/Player/player-stand/0.png");
	anim_idleShot->AddFrame("Resources/Image/Player/player-stand/1.png");
	anim_idleShot->AddFrame("Resources/Image/Player/player-stand/2.png");

	anim_jumpUp->AddFrame("Resources/Image/Player/player-jump/player-jump-1.png");
	anim_jumping->AddFrame("Resources/Image/Player/player-jump/player-jump-2.png");
	anim_jumping->AddFrame("Resources/Image/Player/player-jump/player-jump-3.png");
	anim_jumping->AddFrame("Resources/Image/Player/player-jump/player-jump-4.png");
	anim_jumping->AddFrame("Resources/Image/Player/player-jump/player-jump-5.png");
	anim_jumping->AddFrame("Resources/Image/Player/player-jump/player-jump-6.png");

	AddChild(anim_idle); anim_idle->setVisible(true);
	AddChild(anim_run); anim_run->setVisible(false);
	AddChild(anim_duck); anim_duck->setVisible(false);
	AddChild(anim_runShot); anim_runShot->setVisible(false);
	AddChild(anim_idleShot); anim_idleShot->setVisible(false);
	AddChild(anim_jumpUp); anim_jumpUp->setVisible(false);
	AddChild(anim_jumping); anim_jumping->setVisible(false);

	currentAnim = anim_idle;

	anim_idle->setPos(-anim_idle->getRect().center() + Vec2(0, 40));
	anim_run->setPos(-anim_run->getRect().center() + Vec2(0, 40));
	anim_duck->setPos(-anim_duck->getRect().center() + Vec2(0, 40));
	anim_runShot->setPos(-anim_runShot->getRect().center() + Vec2(0, 40));
	anim_idleShot->setPos(-anim_idleShot->getRect().center() + Vec2(0, 40));
	anim_jumpUp->setPos(-anim_jumpUp->getRect().center() + Vec2(0, 40));
	anim_jumping->setPos(-anim_jumping->getRect().center() + Vec2(0, 40));
}

void Player::Update(float dt)
{
	Unit::Update(dt);

	if (isDie)
		return;

	Movement(dt);
	CheckGround();
	AnimationController();

	/*skill_1_timer += dt;
	if (skill_1_timer > 0.1f) {
		Particle* tmp =
			GAME_MGR.inGame->CreateParticle(P_FADE_OUT, pos + currentAnim->getPos(), currentAnim->getCurrentTexture());
		tmp->setScaleCenter(tmp->getRect().center());
		tmp->setScale(Vec2(scale.x, 1));
		skill_1_timer = 0.0f;
	}*/
}

void Player::CheckGround()
{
	/*if (isGround) {
		for (int x = pos.x + 10; x < (int)pos.x + rect.right - 10; x++) {
			for (int y = pos.y + rect.bottom; y < (int)pos.y + rect.bottom + groundLength; y++) {
				if (bitMap.getBit(x, y) == M_WALL) {
					//pos.x = x;
					pos.y = y - rect.bottom;
					break;
				}
			}
		}
	}*/

	//Check Player Head Collision
	if (currentYPower < 0.0f) {
		for (int x = (int)pos.x + rect.left + groundLength; x < (int)pos.x + rect.left + rect.width() / 2.0f - groundLength; x++) {
			if (bitMap.getBit(x, pos.y) == M_WALL) {
				currentYPower = 0.0f;
				break;
			}
		}
	}

	//Check Player isGround
	if (!isGround && currentYPower > 0.1f) {
		for (int x = (int)pos.x + rect.left + groundLength; x < (int)pos.x + rect.left + rect.width() / 2.0f - groundLength; x++) {
			if (bitMap.getBit(x, pos.y + rect.height()) == M_WALL) {
				isGround = true;

				while (true)
					if (bitMap.getBit(x, pos.y + rect.height()) == M_WALL)
						pos.y -= 1;
					else
						break;
				pos.y += 1;
				break;
			}
		}
	}
	else if (currentYPower >= 0.0f){
		for (int x = (int)pos.x + rect.left + groundLength; x < (int)pos.x + rect.left + rect.width() / 2.0f - groundLength; x++) {
			if (bitMap.getBit(x, pos.y + rect.height()) == M_NONE) {
				isGround = false;
			}
			else if (bitMap.getBit(x, pos.y + rect.height()) == M_WALL) {
				if (isJump)
					continue;
				isGround = true;
				break;
			}
		}
	}
}

void Player::Movement(float dt)
{

	Vec2 tmpPos = pos;

	//Skill_1 : Dash
	if (inputManager->GetKeyState(VK_LSHIFT) == kEY_ON) {
		skill_1_used = true;
	}

	if (skill_1_used) {
		skill_1_particle_timer += dt;
		skill_1_timer += dt;

		if (skill_1_particle_timer > 0.05f) {
			skill_1_particle_timer = 0.0f;

			Particle* tmp =
				GAME_MGR.inGame->CreateParticle(P_FADE_OUT, pos + currentAnim->getPos(), currentAnim->getCurrentTexture());
			tmp->setScaleCenter(tmp->getRect().center());
			tmp->setScale(Vec2(scale.x, 1));
		}

		if (skill_1_timer < 0.5f) {
			tmpPos += Vec2(scale.x, 0) * speed * 2 * dt;
		}
		else {
			skill_1_timer = 0.0f;
			skill_1_used = false;
		}
	}
	else {
		if (inputManager->GetKeyState('A') == kEY_ON)
			currentSpeed = Clamp(currentSpeed - decSpeed * dt * 2, speed, -speed);
		else if (inputManager->GetKeyState('D') == kEY_ON)
			currentSpeed = Clamp(currentSpeed + decSpeed * dt * 2, speed, -speed);
		else
			currentSpeed = Lerp(currentSpeed, 0.0f, 5 * dt);

		if (inputManager->GetKeyState('A') == kEY_ON) {
			scale.x = -1;
			moveDir.x = 1;
			isMove = true;
		}
		else if (inputManager->GetKeyState('D') == kEY_ON) {
			scale.x = 1;
			moveDir.x = 1;
			isMove = true;
		}
		else
			isMove = false;

		tmpPos += moveDir * currentSpeed * dt;
	}

	tmpPos.y += currentYPower * dt;
	if (isGround) {
		currentYPower = 0;

		if (inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
			currentYPower = -jumpPower;
			isGround = false;
			isJump = true;
		}
	}
	else {
		currentYPower += gravity * 100 * dt;
	}


	bool checkWall = false;
	for (int y = (int)tmpPos.y; y < (int)tmpPos.y + rect.bottom - groundLength; y++) {
		if (bitMap.getBit(tmpPos.x + rect.left, y) == M_WALL || bitMap.getBit(tmpPos.x + rect.right, y) == M_WALL) {
			//Check Player Left
			if (currentSpeed < 0.0f) {
				currentSpeed = 0.0f;
				tmpPos.x = pos.x;
				checkWall = true;
				break;
			}

			//Check Player Right
			else {
				currentSpeed = 0.0f;
				tmpPos.x = pos.x;
				checkWall = true;
				break;
			}
		}
	}
	
	pos = tmpPos;

	//Shoot
	if (inputManager->GetKeyState(VK_LCONTROL) == kEY_ON && isGround) {
		isShoot = true;

		if (fire_delay.first >= fire_delay.second) {
			GAME_MGR.inGame->CreateBullet(B_PLAYER, team,
				pos + Vec2(rect.center().x * scale.x, rect.center().y - 27),
				Vec2(scale.x, 0), damage, speed * 5);
			fire_delay.first = 0.0f;
		}
	}
	else
		isShoot = false;
}

void Player::AnimationController()
{
	//Trigger Animation -> Change According to Parameter
	// isJump || skill_1_used: Jump
	// isShoot
	// !isGround && currentYPower > 0.0f : Jumping

	if (isJump || skill_1_used) {
		SwapAnimation(anim_jumpUp);
		isJump = false;
	}
	else if (currentAnim == anim_jumpUp)
		if (currentAnim->getIsEnd())
			SwapAnimation(anim_jumping);
		

	if (!isGround && currentYPower > 0.0f) {
		SwapAnimation(anim_jumping);
	}


	//Parameter Animation -> Change According to Parameter
	//Idle <--> Run <--> RunShoot 
	//     <--> Duck
	//     <--- Jumping

	//Idle <--> Run <--> RunShoot 
	if (currentAnim == anim_idle)
		if (isMove)
			SwapAnimation(anim_run);
		else if (isShoot)
			SwapAnimation(anim_idleShot);

	if (currentAnim == anim_idleShot)
		if (!isShoot)
			SwapAnimation(anim_idle);
		else if (isMove)
			SwapAnimation(anim_runShot);

	if (currentAnim == anim_runShot)
		if (!isShoot)
			SwapAnimation(anim_run);
		else if (!isMove)
			SwapAnimation(anim_idleShot);

	if (currentAnim == anim_run) {
		if (isShoot)
			SwapAnimation(anim_runShot);
		else if (!isMove)
			SwapAnimation(anim_idle);
		else
			SwapAnimation(anim_run);
	}
		

	//Idle <--- Jumping
	if (currentAnim == anim_jumping)
		if (isGround)
			SwapAnimation(anim_idle);
}

void Player::SwapAnimation(Animation* iter)
{
	if (currentAnim == iter)
		return;

	currentAnim->setVisible(false);
	currentAnim = iter;
	currentAnim->RestartAnimation();
	currentAnim->setVisible(true);
}

void Player::setCheckPoint(Vec2 pos)
{
	checkPos = pos;
}

void Player::ReturnCheckPoint()
{
	pos = checkPos;
	currentYPower = -300;

	isDie = false;
}

bool Player::CheckDeathZone()
{
	for (int x = (int)pos.x + rect.left + groundLength; x < (int)pos.x + rect.left + rect.width() / 2.0f - groundLength; x++) {
		if (bitMap.getBit(x, pos.y + rect.height()) == M_DEATH) {
			isDeathZone = true;
			break;
		}
		else
			isDeathZone = false;
	}
	
	if (isDeathZone && !isDie)
		isDie = true;

	return isDeathZone;
}
