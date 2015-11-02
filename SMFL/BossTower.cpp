#include "stdafx.h"
#include "BossTower.h"
#include "BulletManager.h"


const float BossTower::m_BULLET_SPEED = 4;
const float BossTower::m_TIME_BETWEEN_SHOTS = 1000000;

BossTower::BossTower(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect)
{
	m_position = p_position;
	m_sprite.setTexture(*p_tex);
	m_sprite.setTextureRect(p_texRect);
	m_bulletGroup = new StraightBulletGroup();
}


BossTower::~BossTower()
{
}

void BossTower::Init()
{

}

void BossTower::Update(sf::Vector2f p_playerPos, float p_dt)
{
	m_shotTimer += p_dt;
	if (m_shotTimer > m_TIME_BETWEEN_SHOTS)
	{
		m_shotTimer = 0;
		Shoot(p_playerPos);
	}
}

void BossTower::UpdatePosition(sf::Vector2f p_distMoved)
{
	m_position += p_distMoved;
}

sf::Sprite * BossTower::GetTexture()
{
	return &m_sprite;
}

void BossTower::Shoot(sf::Vector2f p_playerPos)
{
	sf::Vector2f direction = m_position - p_playerPos;
	sf::Vector2f origin = sf::Vector2f(m_position.x + m_collisionBox.width / 3, m_position.y + m_collisionBox.height + 12);
	BulletManager::Instance().AddStraight(m_bulletGroup, origin, m_BULLET_SPEED, direction);
}
