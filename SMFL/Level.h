#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

class Level
{
public:
	Level();
	~Level();
	Level(std::vector<sf::Texture>& p_levelTextures, sf::Vector2f p_screenDimensions);
	void Update(sf::Time p_deltaTime);
	void ChangeLevel(int p_level);
	std::vector<sf::Sprite> getSprite();

private:
	// List of Sprites;
	sf::Sprite m_bgSpriteOne, m_bgSpriteTwo;
	sf::IntRect m_bgRectOne, m_bgRectTwo;
	int m_currentLevel = 0;
	std::vector<sf::Texture>  * m_tex;
	sf::Vector2f m_positionOne, m_positionTwo, m_screenDimensions;
};

