#pragma once
#include "Enemy.h"
class HomingEnemy : public Enemy
{
public:
	HomingEnemy(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect);
	~HomingEnemy();
	void Init();
	void Update(sf::Vector2f p_playerPos, float p_dt);
	void RemoveVars(){};

private:
	static const float m_ACCEL;
	static const float m_COLLISIONBOXSIZE;
	static const float m_MAX_SPEED;
};

