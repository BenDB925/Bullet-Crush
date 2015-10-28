#pragma once
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\System\Vector2.hpp"
class UI
{
public:
	~UI();
	static UI& Instance();
	sf::Sprite getSprite();
	void Init(sf::Texture &p_uiTextures);

private:
	UI();
	sf::Sprite m_uiSpriteOne;
	sf::Texture * m_tex;
	sf::Vector2f m_position;
};

