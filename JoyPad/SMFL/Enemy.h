#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "BulletGroup.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	virtual void Init() = 0;
	virtual void Update(sf::Vector2f p_playerPos) = 0;

	sf::Sprite * Enemy::GetTexture();
	sf::IntRect GetCollisionBox() { return m_collisionBox; }
	void SetPosition(sf::Vector2f p_pos);

protected:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	BulletGroup * m_bulletGroup;
	sf::IntRect m_collisionBox;
};

