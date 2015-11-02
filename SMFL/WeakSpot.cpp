#include "stdafx.h"
#include "WeakSpot.h"


WeakSpot::WeakSpot(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect)
{
	m_position = p_position;
	m_sprite.setTexture(*p_tex);
	m_sprite.setTextureRect(p_texRect);
}


WeakSpot::~WeakSpot()
{
}

void WeakSpot::Init()
{

}

void WeakSpot::Update(sf::Vector2f p_playerPos, float p_dt)
{

}

void WeakSpot::UpdatePosition(sf::Vector2f p_distMoved)
{
	m_position += p_distMoved;
}

sf::Sprite * WeakSpot::GetTexture()
{
	return &m_sprite;
}
