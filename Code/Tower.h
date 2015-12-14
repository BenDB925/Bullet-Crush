#pragma once
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\System\Vector2.hpp"
class Tower
{
public:
	Tower();
	~Tower();

	Tower(sf::Sprite, sf::Vector2f, bool);

	void Update(sf::Vector2f);

	sf::Vector2f getPosition();
	sf::Sprite getSprite();
	sf::Vector2f getOrigin(float p_radius);
	int getSize();
	bool getAlive();
	void setAlive(bool);

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_origin;
	int m_size;
	bool m_alive;
};

