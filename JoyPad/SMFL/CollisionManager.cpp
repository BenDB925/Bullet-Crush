#include "stdafx.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "SFML\Graphics\Rect.hpp"
#include "BulletManager.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::Init()
{

}

CollisionManager& CollisionManager::Instance()
{
	static CollisionManager instance;
	return instance;
}

void EnemyPlayer(sf::IntRect p_playerRect)
{
	int enemNum = EnemyManager::Instance().GetEnemyList()->size();

	for (int i = 0; i < enemNum; i++)
	{
		sf::IntRect enemRect = EnemyManager::Instance().GetEnemyList()->at(i)->GetCollisionBox();
		if (p_playerRect.intersects(enemRect))
		{
			int j = 0;
		}

	}
}

void CollisionManager::PlBulletEnemy()
{
	int enemNum = EnemyManager::Instance().GetEnemyList()->size();
	int bulletNum = BulletManager::Instance().GetPlBulletList()->m_bulletList.size();
	std::vector<int> shouldSkipBullet = std::vector<int>();
	std::vector<int> shouldSkipEnemy = std::vector<int>();

	std::vector<Bullet> bullList = BulletManager::Instance().GetPlBulletList()->m_bulletList;
	std::vector<Enemy*>* enemList = EnemyManager::Instance().GetEnemyList();

	for (int i = 0; i < enemNum; i++)
	{
		sf::IntRect enemyRect = EnemyManager::Instance().GetEnemyList()->at(i)->GetCollisionBox();
		for (int j = 0; j < bulletNum; j++)
		{
			sf::IntRect bulletRect = BulletManager::Instance().GetPlBulletList()->m_bulletList.at(j).GetCollisionRect();
			if (enemyRect.intersects(bulletRect))
			{
				bool hasAddedindex = false;
				for (int k = 0; k < shouldSkipEnemy.size(); k++)
				{
					if (shouldSkipEnemy.at(k) == i)
						hasAddedindex = true;
				}
				if (!hasAddedindex)
					shouldSkipEnemy.push_back(i);

				hasAddedindex = false;
				for (int k = 0; k < shouldSkipBullet.size(); k++)
				{
					if (shouldSkipBullet.at(k) == j)
						hasAddedindex = true;
				}
				if (!hasAddedindex)
					shouldSkipBullet.push_back(j);
			}
		}
	}

	for (int i = 0; i < shouldSkipBullet.size(); i++)
	{
		int index = shouldSkipBullet.at(i);
		if (index < BulletManager::Instance().GetPlBulletList()->m_bulletList.size())
			BulletManager::Instance().GetPlBulletList()->m_bulletList.erase(BulletManager::Instance().GetPlBulletList()->m_bulletList.begin() + index);
	}

	for (int i = 0; i < shouldSkipEnemy.size(); i++)
	{
		int index = shouldSkipEnemy.at(i);
		if (index < EnemyManager::Instance().GetEnemyList()->size())
			EnemyManager::Instance().GetEnemyList()->erase(EnemyManager::Instance().GetEnemyList()->begin() + index);
	}
}

void CollisionManager::CheckCollisions(sf::IntRect p_playerRect)
{
	EnemyPlayer(p_playerRect);
	PlBulletEnemy();
}
