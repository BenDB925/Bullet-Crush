#include "stdafx.h"
#include "StraightBulletGroup.h"


StraightBulletGroup::StraightBulletGroup()
{
	
}


StraightBulletGroup::~StraightBulletGroup()
{
}

int StraightBulletGroup::AddBullet(sf::Vector2f p_position, float p_velocity, sf::Vector2f p_direction, sf::Texture *&p_tex, sf::IntRect p_texCoords, int p_radius, Bullet::BulletType p_type)
{
	m_bulletRadius = p_radius;
	sf::Vector2f vel(p_velocity * p_direction.x, p_velocity * p_direction.y);
	m_bulletList.push_back(Bullet(p_position, vel, p_tex, p_texCoords, p_radius, p_type));
	return m_bulletList.size() - 1;
}
