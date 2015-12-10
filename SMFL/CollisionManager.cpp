#include "stdafx.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "SFML\Graphics\Rect.hpp"
#include "BulletManager.h"
#include "Enemy.h"


struct CorrespondingEnem 
{
	CorrespondingEnem(){}
	CorrespondingEnem(Bullet * p_bull, int p_enem)
	{
		m_bull = p_bull;
		m_enemIndex = p_enem;
	}
	Bullet* m_bull;
	int  m_enemIndex;
};

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
	//std::vector<int> shouldSkipBullet = std::vector<int>();
	std::vector<CorrespondingEnem> correspondingList = std::vector<CorrespondingEnem>();


	std::vector<int> shouldSkipEnemy = std::vector<int>();

	std::vector<Bullet> bullList = BulletManager::Instance().GetPlBulletList()->m_bulletList;
	std::vector<Enemy*>* enemList = EnemyManager::Instance().GetEnemyList();

	for (int i = 0; i < enemNum; i++)
	{
		sf::IntRect enemyRect = EnemyManager::Instance().GetEnemyList()->at(i)->GetCollisionBox();
		for (int j = 0; j < bulletNum; j++)
		{
			sf::IntRect bulletRect = BulletManager::Instance().GetPlBulletList()->m_bulletList.at(j).GetCollisionRect();
			if (enemyRect.intersects(bulletRect) && EnemyManager::Instance().GetEnemyList()->at(i)->GetAliveState() == Enemy::AliveState::IS_ALIVE)
			{
				bool hasAddedIndex = false;
				//for (int k = 0; k < shouldSkipEnemy.size(); k++)
				//{
				//	if (shouldSkipEnemy.at(k) == i)
				//		hasAddedindex = true;
				//}
				//if (!hasAddedindex)
					//shouldSkipEnemy.push_back(i);
				for (int k = 0; k < correspondingList.size(); k++)
				{
					if (correspondingList.at(k).m_bull == &BulletManager::Instance().GetPlBulletList()->m_bulletList.at(j))
						hasAddedIndex = true;
					if (correspondingList.at(k).m_enemIndex == i)
						hasAddedIndex = true;
				}
				if (!hasAddedIndex)
					correspondingList.push_back(CorrespondingEnem(&BulletManager::Instance().GetPlBulletList()->m_bulletList.at(j), i));

				//hasAddedindex = false;
				//for (int k = 0; k < shouldSkipBullet.size(); k++)
				//{
				//	if (shouldSkipBullet.at(k) == j)
				//		hasAddedindex = true;
				//}
				//if (!hasAddedindex)
				//	shouldSkipBullet.push_back(j);
			}
		}
	}

	//for (int i = 0; i < shouldSkipBullet.size(); i++)
	//{
	//	int index = shouldSkipBullet.at(i);
	//	if (index < BulletManager::Instance().GetPlBulletList()->m_bulletList.size())
	//		BulletManager::Instance().GetPlBulletList()->m_bulletList.erase(BulletManager::Instance().GetPlBulletList()->m_bulletList.begin() + index);
	//}

	//for (int i = 0; i < shouldSkipEnemy.size(); i++)
	//{
	//	int index = shouldSkipEnemy.at(i);
	//	if (index < EnemyManager::Instance().GetEnemyList()->size())
	//	{
	//		//if ()
	//		EnemyManager::Instance().GetEnemyList()->at(index)->ReduceHealth(1);
	//	}
	//}
	
	for (int i = 0; i < correspondingList.size(); i++)
	{
		for (int j = 0; j < BulletManager::Instance().GetPlBulletList()->m_bulletList.size(); j++)
		{
			if (&BulletManager::Instance().GetPlBulletList()->m_bulletList.at(j) == correspondingList.at(i).m_bull)
			{
				BulletManager::Instance().GetPlBulletList()->m_bulletList.erase(BulletManager::Instance().GetPlBulletList()->m_bulletList.begin() + j);
			}
		}		
	}

	for (int i = 0; i < correspondingList.size(); i++)
	{
		if (correspondingList.at(i).m_bull->GetType() == Bullet::BLASTER)
			EnemyManager::Instance().GetEnemyList()->at(correspondingList.at(i).m_enemIndex)->ReduceHealth(10);

		else if (correspondingList.at(i).m_bull->GetType() == Bullet::SPREAD)
			EnemyManager::Instance().GetEnemyList()->at(correspondingList.at(i).m_enemIndex)->ReduceHealth(1);
	}
}

void CollisionManager::CheckCollisions(sf::IntRect p_playerRect)
{
	EnemyPlayer(p_playerRect);
	PlBulletEnemy();
}
