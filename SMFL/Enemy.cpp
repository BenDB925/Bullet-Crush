#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	delete(m_bulletGroup);
}

sf::Sprite * Enemy::GetTexture()
{
	return &m_sprite;
}

void Enemy::SetPosition(sf::Vector2f p_pos)
{
	m_position = p_pos;
}

bool Enemy::CheckOffScreen(sf::Vector2f p_screenDimensions)
{
	if (m_position.x > p_screenDimensions.x || m_position.x < -m_collisionBox.width / 2 ||
		m_position.y > p_screenDimensions.y)
	{
		return true;

	}
	else
		return false;
}
