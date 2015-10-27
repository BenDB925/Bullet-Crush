#pragma once
#include "stdafx.h"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\System\Vector2.hpp"
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();


	void Init();

	static CollisionManager& Instance();

	void CheckCollisions(sf::IntRect p_playerPos);
private:
	void PlBulletEnemy();
};

