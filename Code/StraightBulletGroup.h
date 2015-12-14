#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "BulletGroup.h"
class StraightBulletGroup : public BulletGroup
{
public:
	StraightBulletGroup();
	~StraightBulletGroup();
	int AddBullet(sf::Vector2f p_position, float p_velocity, sf::Vector2f p_direction, sf::Texture *&p_tex, sf::IntRect p_texCoords, int p_radius = 5, Bullet::BulletType p_type = Bullet::DEFAULT);
};

