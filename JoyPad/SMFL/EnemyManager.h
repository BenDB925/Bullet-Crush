#pragma once
#include <vector>
#include "Enemy.h"
#include "SFML\Graphics\RenderWindow.hpp"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	static EnemyManager& Instance();
	void Init(sf::Texture& p_tex);
	void Update(sf::Vector2f p_playerPos);
	void Draw(sf::RenderWindow& p_window);
	std::vector<Enemy*> * GetEnemyList();

private:
	std::vector<Enemy*> m_enemyList;
	sf::Texture *m_textureAtlas;

	sf::IntRect m_HOMING_ENEM_COORDS;

	void AddHomingEnem();
};

