#pragma once
#include "Enemy.h"
#include "StraightBulletGroup.h"
class SlowShootyEnem : public Enemy
{
public:
	SlowShootyEnem(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect);
	~SlowShootyEnem();
	void Init();
	void Update(sf::Vector2f p_playerPos, float p_dt);
	void RemoveVars();

private:
	void Shoot();
	
	static const float m_ACCEL;
	static const float m_COLLISIONBOXSIZEWIDTH;
	static const float m_COLLISIONBOXSIZEHEIGHT;
	static const float m_MAX_SPEED;
	static const float m_BULLET_SPEED;
	static const float m_TIME_BETWEEN_SHOTS;
	float m_shotTimer;
	StraightBulletGroup *m_bulletGroup;
};

