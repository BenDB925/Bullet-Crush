#pragma once
#include <vector>
#include "Enemy.h"
#include "SFML\Graphics\RenderWindow.hpp"
#include "Boss.h"

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
	Boss * GetBoss();
	bool ShouldCheckBoss();
private:
	std::vector<Enemy*> m_enemyList;
	Boss m_boss;
	sf::Texture *m_textureAtlas;

	static const sf::IntRect m_HOMING_ENEM_COORDS;
	static const sf::IntRect m_SLOW_SHOOTY_ENEM_COORDS;
	static const sf::IntRect m_BOSS_COORDS;

	void ManageEnemySpawning(sf::Vector2f p_screenDimensions, sf::Vector2f p_playerPos, float p_dt);

	void AddHomingEnem(sf::Vector2f p_position);
	void AddSlowShootyEnem(sf::Vector2f p_position);

	void AddHomingWave(sf::Vector2f p_screenDimensions);
	void AddSlowWave(sf::Vector2f p_screenDimensions);

	//Enemy timer shit
	const float m_TIME_BETWEEN_HOMING_WAVES = 150;
	const float m_TIME_BETWEEN_SLOW_WAVES = 70;
	float m_waveTimer = 0;
	const int m_NUM_WAVES_BETWEEN_BOSS = 3;
	int m_waveCounter = 5;
};
