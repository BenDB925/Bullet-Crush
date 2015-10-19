#include "stdafx.h"
#include "EnemyManager.h"
#include "HomingEnemy.h"


EnemyManager::EnemyManager()
{
	m_enemyList = std::vector<Enemy*>(); 
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

void EnemyManager::Init()
{
	AddHomingEnem();
}

void EnemyManager::Update()
{

}

void EnemyManager::Draw()
{

}

void EnemyManager::AddHomingEnem()
{
	m_enemyList.push_back(new HomingEnemy());
	m_enemyList.at(m_enemyList.size() - 1)->Init();
}
