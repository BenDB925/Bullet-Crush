#include "stdafx.h"
#include "EnemyManager.h"
#include "HomingEnemy.h"


EnemyManager::EnemyManager()
{
	m_enemyList = std::vector<Enemy*>();
	m_HOMING_ENEM_COORDS = sf::IntRect(11, 12, 42, 64);
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
	AddHomingEnem();
}

void EnemyManager::Update(sf::Vector2f p_playerPos)
{
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList.at(i)->Update(p_playerPos);
	}
}

void EnemyManager::Draw(sf::RenderWindow& p_window)
{
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		p_window.draw(*m_enemyList.at(i)->GetTexture());
	}
}

void EnemyManager::AddHomingEnem()
{
	m_enemyList.push_back(new HomingEnemy(m_textureAtlas, m_HOMING_ENEM_COORDS));
	m_enemyList.at(m_enemyList.size() - 1)->Init();
}

std::vector<Enemy*> * EnemyManager::GetEnemyList()
{
	return &m_enemyList;
}
