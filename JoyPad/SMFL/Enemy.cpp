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