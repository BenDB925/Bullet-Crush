#pragma once
#include "Enemy.h"
#include "StraightBulletGroup.h"

class BossTower : public Enemy
{
public:
	BossTower(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect, sf::IntRect p_collRect);
	~BossTower();

	void Init();
	void Update(sf::Vector2f p_playerPos, float p_dt);
	void RemoveVars(){};
	void UpdatePosition(sf::Vector2f p_distMoved);
	sf::Sprite * GetTexture();

private:
	void Shoot(sf::Vector2f p_playerPos);
	StraightBulletGroup * m_bulletGroup;
	float m_shotTimer;
	static const float m_BULLET_SPEED;
	static const float m_TIME_BETWEEN_SHOTS;
};

