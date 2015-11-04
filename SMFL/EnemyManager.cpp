#include "stdafx.h"
#include "EnemyManager.h"
#include "HomingEnemy.h"
#include "SlowShootyEnem.h"
#include "Boss.h"

bool hasHomingSpawned = false;

EnemyManager::EnemyManager()
{
	m_enemyList = std::vector<Enemy*>();
	m_HOMING_ENEM_COORDS = sf::IntRect(0, 301, 58, 50);
	m_SLOW_SHOOTY_ENEM_COORDS = sf::IntRect(0, 301, 58, 50);
}


EnemyManager::~EnemyManager()
{
	m_enemyList.clear();
}

EnemyManager& EnemyManager::Instance()
{
	static EnemyManager instance;
	return instance;
}

void EnemyManager::Init(sf::Texture& p_tex)
{
	m_textureAtlas = &p_tex;
}

void EnemyManager::Update(sf::Vector2f p_playerPos, float p_dt, sf::Vector2f p_screenDimensions)
{
	m_waveTimer += p_dt / 10000;
	

	ManageEnemySpawning(p_screenDimensions);

	for (int i = 0; i < m_enemyList.size(); i++)
	{
		if (m_enemyList.at(i)->CheckOffScreen(p_screenDimensions))
		{
			m_enemyList.at(i)->RemoveVars();
			m_enemyList.erase(m_enemyList.begin() + i);			
		}
	}

	for (int i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList.at(i)->Update(p_playerPos, p_dt);
		if (m_enemyList.at(i)->UpdateAnim(p_dt) == false)
		{
			m_enemyList.at(i)->RemoveVars();
			m_enemyList.erase(m_enemyList.begin() + i);
		}
	}
}

void EnemyManager::Draw(sf::RenderWindow& p_window)
{
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		p_window.draw(*m_enemyList.at(i)->GetTexture());
	}
}

void EnemyManager::AddHomingEnem(sf::Vector2f p_position)
{
	m_enemyList.push_back(new HomingEnemy(p_position, m_textureAtlas, m_HOMING_ENEM_COORDS));
	m_enemyList.at(m_enemyList.size() - 1)->Init();
}

std::vector<Enemy*> * EnemyManager::GetEnemyList()
{
	return &m_enemyList;
}

void EnemyManager::AddSlowShootyEnem(sf::Vector2f p_position)
{
	m_enemyList.push_back(new SlowShootyEnem(p_position, m_textureAtlas, m_SLOW_SHOOTY_ENEM_COORDS));
	m_enemyList.at(m_enemyList.size() - 1)->Init();
}

void EnemyManager::AddHomingWave(sf::Vector2f p_screenDimensions)
{
	if (m_waveTimer > m_TIME_BETWEEN_HOMING_WAVES)
	{
		m_waveTimer = 0;
		hasHomingSpawned = false;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				AddHomingEnem(sf::Vector2f(rand() % (int)p_screenDimensions.x, -100 - (j * 50)));
			}
		}
	}
}

void EnemyManager::AddSlowWave(sf::Vector2f p_screenDimensions)
{
	if (m_waveTimer > m_TIME_BETWEEN_SLOW_WAVES && !hasHomingSpawned)
	{
		hasHomingSpawned = true;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				AddSlowShootyEnem(sf::Vector2f(sf::Vector2f(rand() % (int)p_screenDimensions.x, -100 - (j * 50))));
			}
		}
	}
}

void EnemyManager::ManageEnemySpawning(sf::Vector2f p_screenDimensions)
{
	AddHomingWave(p_screenDimensions);
	AddSlowWave(p_screenDimensions);
	
	//m_boss = Boss();
}
