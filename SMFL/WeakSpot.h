#pragma once
#include "Enemy.h"

class WeakSpot :public Enemy
{
public:
	WeakSpot(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect);
	~WeakSpot();

	void Init();
	void Update(sf::Vector2f p_playerPos, float p_dt);
	void UpdatePosition(sf::Vector2f p_distMoved);
	sf::Sprite * GetTexture();
	void RemoveVars(){};
};

