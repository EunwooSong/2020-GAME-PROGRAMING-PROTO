#pragma once
#include "Sprite.h"
class Particle :
	public Sprite
{
private:
	ParticleType type;
	bool isMove;
	float moveSpeed;
	float targetAngle;
	float fadeSpeed;
	float moveDecSpeed;
	bool isFadeIn;

	Object* target;

	bool isEnd;

public:
	Particle(string p, ParticleType type, float fadeSpeed = 5, float moveSpeed = 50, float targetAngle = 0);
	Particle(LPDIRECT3DTEXTURE9 p, ParticleType type, float fadeSpeed = 5, float moveSpeed = 50, float targetAngle = 0);
	~Particle();

	void Update(float dt);
	void setMoveDecSpeed(float speed);
	void setTargetAngle(float targetAngle);
	void setMoveSpeed(float speed);
	void setTarget(Object* target);
	bool getIsEnd();
};


