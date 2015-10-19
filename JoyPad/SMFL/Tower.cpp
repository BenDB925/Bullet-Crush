#include "stdafx.h"
#include "Tower.h"


Tower::Tower()
{
}

Tower::Tower(sf::Sprite p_sprite, sf::Vector2f p_pos)
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

sf::Vector2f Tower::getOrigin()
{
	return sf::Vector2f(m_position.x + 5, m_position.y + 5);
}

int Tower::getSize()
{
	return m_size;
}
