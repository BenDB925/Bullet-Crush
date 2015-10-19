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
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	BulletGroup * m_bulletGroup;
};

