#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::Bullet(sf::Vector2f p_position, sf::Vector2f p_velocity, sf::Texture *&p_tex, sf::IntRect p_texCoords)
{
	m_position = p_position;
	m_velocity = p_velocity;

	m_sprite.setTexture(*p_tex);
	m_sprite.setTextureRect(p_texCoords);
	m_sprite.setPosition(m_position);
	m_radius = 5;
	//m_circleShape = sf::CircleShape(10, 16);
	//m_circleShape.setPosition(m_position);
}


Bullet::~Bullet()
{
}

sf::Sprite * Bullet::GetTexture()
{
	return &m_sprite;
}

void Bullet::Update(sf::Time p_deltaTime)
{
	m_position += sf::Vector2f(m_velocity.x * p_deltaTime.asSeconds() * 100, m_velocity.y * p_deltaTime.asSeconds() * 100);
	//m_circleShape.setPosition(m_position);
	m_sprite.setPosition(m_position);
}

sf::Vector2f Bullet::GetPosition()
{
	return m_position;
}

