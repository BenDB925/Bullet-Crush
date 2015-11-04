#include "stdafx.h"
#include "SlowShootyEnem.h"
#include "BulletManager.h"

const float SlowShootyEnem::m_ACCEL = 0.00001;
const float SlowShootyEnem::m_MAX_SPEED = 0.0002;
const float SlowShootyEnem::m_COLLISIONBOXSIZE = 50;
const float SlowShootyEnem::m_BULLET_SPEED = 4;
const float SlowShootyEnem::m_TIME_BETWEEN_SHOTS = 1000000;

SlowShootyEnem::SlowShootyEnem(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect)
{
	m_sprite = sf::Sprite(*p_tex);
	m_sprite.setTextureRect(p_texRect);
	m_position = p_position;
	m_sprite.setPosition(m_position);
	m_shotTimer = std::rand() % (int)m_TIME_BETWEEN_SHOTS;
	m_bulletGroup = new StraightBulletGroup();
	BulletManager::Instance().AddBulletGroup(*m_bulletGroup);
}


SlowShootyEnem::~SlowShootyEnem()
{

}

void SlowShootyEnem::Init()
{

}

void SlowShootyEnem::Update(sf::Vector2f p_playerPos, float p_dt)
{
	if (m_velocity.y < m_MAX_SPEED)
		m_velocity.y +=  m_ACCEL;
	m_position += m_velocity * p_dt;
	m_sprite.setPosition(m_position);
	m_collisionBox = sf::IntRect(m_position.x - m_COLLISIONBOXSIZE / 2,
		m_position.y - m_COLLISIONBOXSIZE / 2,
		m_COLLISIONBOXSIZE,
		m_COLLISIONBOXSIZE);

	m_shotTimer += p_dt;
	if (m_shotTimer > m_TIME_BETWEEN_SHOTS && m_aliveState == Enemy::AliveState::IS_ALIVE)
	{
		m_shotTimer = 0;
		Shoot();
	}
}

void SlowShootyEnem::Shoot()
{
	sf::Vector2f direction = sf::Vector2f(0,1);
	sf::Vector2f origin = sf::Vector2f(m_position.x + m_collisionBox.width / 3, m_position.y + m_collisionBox.height + 12);
	BulletManager::Instance().AddStraight(m_bulletGroup, origin, m_BULLET_SPEED, direction);
}

void SlowShootyEnem::RemoveVars()
{
	BulletManager::Instance().RemoveBulletGroup(m_bulletGroup);
}
