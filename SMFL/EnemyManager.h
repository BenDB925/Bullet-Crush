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
	void Update(sf::Vector2f p_playerPos, float p_dt, sf::Vector2f p_screenDimensions);
	void Draw(sf::RenderWindow& p_window);
	std::vector<Enemy*> * GetEnemyList();

private:
	std::vector<Enemy*> m_enemyList;
	sf::Texture *m_textureAtlas;

	sf::IntRect m_HOMING_ENEM_COORDS;
	sf::IntRect m_SLOW_SHOOTY_ENEM_COORDS;

	void AddHomingEnem(sf::Vector2f p_position);
	void AddSlowShootyEnem(sf::Vector2f p_position);

	//Enemy timer shit
	const float m_TIME_BETWEEN_HOMING_WAVES = 200;
	const float m_TIME_BETWEEN_SLOW_WAVES = 60;
	float m_waveTimer = 0;
};

