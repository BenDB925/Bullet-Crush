#include "stdafx.h"
#include "Level.h"


Level::Level()
{
}

Level::Level(std::vector<sf::Texture>& p_levelTextures, sf::Vector2f p_screenDimensions):
m_tex(&p_levelTextures),
m_screenDimensions(p_screenDimensions),
m_bgRectOne(sf::IntRect(0,0,p_screenDimensions.x, p_screenDimensions.y * 0.5)),
m_bgRectTwo(sf::IntRect(0, p_screenDimensions.y * 0.5, p_screenDimensions.x, p_screenDimensions.y * 0.5)),
m_positionOne(sf::Vector2f(0,-p_screenDimensions.y)),
m_positionTwo(sf::Vector2f(0,0))
{

	m_bgSpriteOne.setTexture(m_tex->at(0));
	m_bgSpriteOne.setTextureRect(m_bgRectOne);
	m_bgSpriteOne.setScale(sf::Vector2f(1, 2));
	m_bgSpriteOne.setPosition(sf::Vector2f(-m_screenDimensions.y, 0));

	m_bgSpriteTwo.setTexture(m_tex->at(0));
	m_bgSpriteTwo.setTextureRect(m_bgRectTwo);
	m_bgSpriteTwo.setScale(sf::Vector2f(1, 2));
	m_bgSpriteOne.setPosition(sf::Vector2f(m_screenDimensions.y, 0));
}


Level::~Level()
{
}

void Level::Update(sf::Time p_deltaTime)
{
	m_positionOne.y += p_deltaTime.asSeconds() * 60;
	m_positionTwo.y += p_deltaTime.asSeconds() * 60;

	if (m_positionOne.y > m_screenDimensions.y)
		m_positionOne.y = -m_screenDimensions.y;
	if (m_positionTwo.y > m_screenDimensions.y)
		m_positionTwo.y = -m_screenDimensions.y;

	m_bgSpriteOne.setPosition(m_positionOne);
	m_bgSpriteTwo.setPosition(m_positionTwo);
}

void Level::ChangeLevel(int p_level)
{

}

std::vector<sf::Sprite> Level::getSprite()
{
	std::vector<sf::Sprite> sprites;
	sprites.push_back(m_bgSpriteOne);
	sprites.push_back(m_bgSpriteTwo);
	return sprites;
}
