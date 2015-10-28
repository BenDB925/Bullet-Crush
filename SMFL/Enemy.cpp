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
