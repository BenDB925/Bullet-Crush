#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\CircleShape.hpp"
#include "SFML\System\Time.hpp"
#include "SFML\Graphics\Sprite.hpp"




class Bullet
{
public:
	Bullet();
	Bullet(sf::Vector2f p_position, sf::Vector2f p_velocity, sf::Texture *&p_tex, sf::IntRect p_texCoords);
	~Bullet();
	void Update(sf::Time p_deltaTime);

	sf::Sprite * GetTexture();
	sf::Vector2f GetPosition();

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	int m_radius;
	sf::Sprite m_sprite;
	static const float m_RADTODEG;
};

