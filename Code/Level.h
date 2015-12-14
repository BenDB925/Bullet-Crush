#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

class Level
{
public:
	Level();
	~Level();
	Level(std::vector<sf::Texture>& p_levelTextures, sf::Vector2f p_screenDimensions);
	void Update(float p_deltaTime);
	void ChangeLevel(int p_level);
	sf::Sprite getSprite();

private:
	// List of Sprites;
	sf::Sprite m_bgSprite;
	sf::IntRect m_bgRect;
	int m_currentLevel = 0;
	std::vector<sf::Texture>  * m_tex;
	sf::Vector2f m_positionOne, m_screenDimensions;
	float m_bgY;
	int offsetY;
};

