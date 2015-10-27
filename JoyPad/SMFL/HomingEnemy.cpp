#include "stdafx.h"
#include "HomingEnemy.h"

const float HomingEnemy::m_ACCEL = 0.05;
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

HomingEnemy::HomingEnemy(sf::Texture * p_tex, sf::IntRect p_texRect)
{
	m_sprite = sf::Sprite(*p_tex);
	m_sprite.setTextureRect(p_texRect);
	m_position = sf::Vector2f(100, 100);
	m_sprite.setPosition(m_position);
}


HomingEnemy::~HomingEnemy()
{
}

void HomingEnemy::Init()
{
}

void HomingEnemy::Update(sf::Vector2f p_playerPos)
{
	sf::Vector2f vecBetweenPlEnem = p_playerPos - m_position;
	vecBetweenPlEnem = Normalise(vecBetweenPlEnem);
	m_velocity = vecBetweenPlEnem * m_ACCEL;
	m_position += m_velocity;
	m_sprite.setPosition(m_position);
	m_collisionBox = sf::IntRect(m_position.x - m_COLLISIONBOXSIZE / 2,
		m_position.y - m_COLLISIONBOXSIZE / 2,
		m_COLLISIONBOXSIZE,
		m_COLLISIONBOXSIZE);
}