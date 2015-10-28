#include "stdafx.h"
#include "UI.h"


UI::~UI()
{
}

UI& UI::Instance()
{
	static UI instance;
	return instance;
}

sf::Sprite UI::getSprite()
{
	return m_uiSpriteOne;
}

UI::UI()
{
}
void UI::Init(sf::Texture &p_uiTextures)
{
	m_tex = &p_uiTextures;
	m_uiSpriteOne.setTexture(*m_tex);
	m_uiSpriteOne.setTextureRect(sf::IntRect(0, 200, 600, 89));
	m_uiSpriteOne.setPosition(sf::Vector2f(0, 0));
}
