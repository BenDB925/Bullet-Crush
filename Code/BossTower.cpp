#include "stdafx.h"
#include "BossTower.h"
#include "BulletManager.h"


const float BossTower::m_BULLET_SPEED = 4;
const float BossTower::m_TIME_BETWEEN_SHOTS = 1000000;


double DistanceVec(double dX0, double dY0, double dX1, double dY1)
{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

sf::Vector2f NormaliseVec(sf::Vector2f * p_vec)
{
	float length = DistanceVec(0, 0, p_vec->x, p_vec->y);

	if (length != 0)
		return sf::Vector2f(p_vec->x / length, p_vec->y / length);
	else
		return sf::Vector2f(0, 0);
}

BossTower::BossTower(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect, sf::IntRect p_collRect)
{
	m_collisionBox = p_collRect;
	m_position = p_position;
	m_sprite.setPosition(m_position);
	m_sprite.setTexture(*p_tex);
	m_sprite.setTextureRect(p_texRect);
	m_bulletGroup = new StraightBulletGroup();
	BulletManager::Instance().AddBulletGroup(*m_bulletGroup);
	m_shotTimer = 0;
	m_health = 1000;
}


BossTower::~BossTower()
{
	//if (m_bulletGroup != nullptr && m_bulletGroup != NULL)
	//	delete m_bulletGroup;
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
	m_sprite.setPosition(m_position);
	m_collisionBox.left += p_distMoved.x;
	m_collisionBox.top += p_distMoved.y;
}

sf::Sprite * BossTower::GetTexture()
{
	return &m_sprite;
}

void BossTower::Shoot(sf::Vector2f p_playerPos)
{
	//sf::Vector2f direction = p_playerPos - m_position;
	//direction = NormaliseVec(&direction);
	//sf::Vector2f origin = sf::Vector2f(m_position.x + m_collisionBox.width / 3, m_position.y + m_collisionBox.height + 12);
	//BulletManager::Instance().AddStraight(m_bulletGroup, origin, m_BULLET_SPEED, direction);
	// 


	BulletManager::Instance().AddSpiral(m_position, 16, true);
}
