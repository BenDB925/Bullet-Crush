#pragma once
#include "Bullet.h"
#include "SFML\System\Clock.hpp"
#include "SFML\Graphics\Rect.hpp"
class BulletGroup
{
public:
	BulletGroup();
	~BulletGroup();
	std::vector<Bullet> m_bulletList;

	void Update(sf::Time p_deltaTime, sf::Vector2f p_screenDimensions);
	float GetRadius();
	void SetShouldBeDestroyed(bool p_shouldBeDestroyed);
	bool GetShouldBeDestroyed();
	bool ShouldBeDestroyed();
	void AddBullet(sf::Vector2f p_position, float p_velocity, sf::Vector2f p_direction, sf::Texture *&p_tex, sf::IntRect p_texCoords){}

protected:
	sf::Vector2f m_position;
	int m_bulletRadius;
	bool m_shouldBeDestroyed;
	sf::Rect<float> m_textureCoords;
};

