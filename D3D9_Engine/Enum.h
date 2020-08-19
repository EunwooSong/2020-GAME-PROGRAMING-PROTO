#pragma once
enum ParticleType {
	P_FADE_IN,
	P_FADE_OUT,
	P_FADE_IN_OUT,
	P_MOVE_RIT,
	P_COIN
};

enum UnitType {
	U_NONE,
	U_PLAYER,
	U_BULLET,
	U_ENEMY,
	U_STONE,
	U_PLATE,
	U_ITEM
};

enum Team {
	PLAYER,
	ENEMY
};

enum ItemType {
	I_HEAL,
	I_POWER,
	I_BOOM
};

enum MapCollision {
	M_NONE,
	M_WALL,
	M_DEATH,
	M_CLEAR,
	M_OUT_MAP
};

enum BulletType {
	B_PLAYER
};

enum EffectType {
	E_BULLET,
	E_EXPLOSION
};