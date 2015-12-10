#include "stdafx.h"
#include "Tower.h"

Tower::Tower()
{
}

Tower::Tower(sf::Sprite p_sprite, sf::Vector2f p_pos, bool p_alive) :
m_sprite(p_sprite),
m_position(p_pos),
m_alive(p_alive)
{
	m_size = 20;
	m_sprite = p_sprite;
	m_position = p_pos;
	m_sprite.setPosition(m_position);
}


Tower::~Tower()
{
}

// Getters
///////////////////////////
sf::Vector2f Tower::getPosition()
{
	return m_position;
}

sf::Sprite Tower::getSprite()
{
	return m_sprite;
}

void Tower::Update(sf::Vector2f p_velocity)
{
	m_position += p_velocity;
	m_sprite.setPosition(m_position);
}

sf::Vector2f Tower::getOrigin(float p_radius)
{
	return sf::Vector2f(m_position.x + (m_size * 0.5) - p_radius, m_position.y + (m_size * 0.5) - p_radius);
}

int Tower::getSize()
{
	return m_size;
}

void Tower::setAlive(bool p_alive)
{
	m_alive = p_alive;
}

bool Tower::getAlive()
{
	return m_alive;
}
