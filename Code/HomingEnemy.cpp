#include "stdafx.h"
#include "HomingEnemy.h"

const float HomingEnemy::m_ACCEL = 0.00001;
const float HomingEnemy::m_MAX_SPEED = 0.0005;
const float HomingEnemy::m_COLLISIONBOXSIZE = 50;

float myDistFormula(sf::Vector2f x, sf::Vector2f y)
{
	float distance, tempx, tempy;
	tempx = (x.x - y.x);
	tempx = pow(tempx, 2.0f);
	tempy = (x.y - y.y);
	tempy = pow(tempy, 2.0f);
	distance = tempx + tempy;
	distance = sqrt(distance);
	return distance;
}

sf::Vector2f Normalise(sf::Vector2f p_vec)
{
	float dist = myDistFormula(sf::Vector2f(0, 0), p_vec);
	p_vec /= dist;
	return p_vec;
}

HomingEnemy::HomingEnemy(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect)
{
	m_sprite = sf::Sprite(*p_tex);
	m_sprite.setTextureRect(p_texRect);
	m_position = p_position;
	m_sprite.setPosition(m_position);
	m_health = 2;
}


HomingEnemy::~HomingEnemy()
{
}

void HomingEnemy::Init()
{
}

void HomingEnemy::Update(sf::Vector2f p_playerPos, float p_dt)
{
	sf::Vector2f vecBetweenPlEnem = p_playerPos - m_position;
	vecBetweenPlEnem = Normalise(vecBetweenPlEnem);
	if (m_velocity.x < m_MAX_SPEED && m_velocity.y < m_MAX_SPEED)
		m_velocity += vecBetweenPlEnem * m_ACCEL;
	m_position += m_velocity * p_dt;
	m_sprite.setPosition(m_position);
	m_collisionBox = sf::IntRect(m_position.x + 24, m_position.y, 58, 50);
}

