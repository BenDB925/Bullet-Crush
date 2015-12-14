#include "stdafx.h"
#include "SlowShootyEnem.h"
#include "BulletManager.h"


const float SlowShootyEnem::m_ACCEL = 0.00001;
const float SlowShootyEnem::m_MAX_SPEED = 0.0002;
const float SlowShootyEnem::m_COLLISIONBOXSIZEWIDTH = 58;
const float SlowShootyEnem::m_COLLISIONBOXSIZEHEIGHT = 50;
const float SlowShootyEnem::m_BULLET_SPEED = 4;
const float SlowShootyEnem::m_TIME_BETWEEN_SHOTS = 1000000;

SlowShootyEnem::SlowShootyEnem(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect)
{
	m_sprite = sf::Sprite(*p_tex);
	m_sprite.setTextureRect(p_texRect);
	m_position = p_position;
	m_sprite.setPosition(m_position);
	m_shotTimer = (int(std::rand()) % (int)2000) * (m_TIME_BETWEEN_SHOTS / 2000);
	m_bulletGroup = new StraightBulletGroup();
	BulletManager::Instance().AddBulletGroup(*m_bulletGroup);
	m_health = 4;
}


SlowShootyEnem::~SlowShootyEnem()
{
	delete m_bulletGroup;
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
	m_collisionBox = sf::IntRect(m_position.x, m_position.y, m_COLLISIONBOXSIZEWIDTH, m_COLLISIONBOXSIZEHEIGHT);

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
	// Need to take away the offset of the bullet
	sf::Vector2f origin = sf::Vector2f(m_position.x + m_COLLISIONBOXSIZEWIDTH * 0.5 -5, m_position.y + m_COLLISIONBOXSIZEHEIGHT * 0.5);
	BulletManager::Instance().AddStraight(m_bulletGroup, origin, m_BULLET_SPEED, direction);
}

void SlowShootyEnem::RemoveVars()
{
	BulletManager::Instance().RemoveBulletGroup(m_bulletGroup);
}
