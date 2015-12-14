#include "stdafx.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "SFML\Graphics\Rect.hpp"
#include "BulletManager.h"
#include "Enemy.h"
#include "Player.h"


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
				for (int k = 0; k < correspondingList.size(); k++)
				{
					if (correspondingList.at(k).m_bull == &BulletManager::Instance().GetPlBulletList()->m_bulletList.at(j))
						hasAddedIndex = true;
					if (correspondingList.at(k).m_enemIndex == i)
						hasAddedIndex = true;
				}
				if (!hasAddedIndex)
					correspondingList.push_back(CorrespondingEnem(&BulletManager::Instance().GetPlBulletList()->m_bulletList.at(j), i));
			}
		}
	}

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

void CollisionManager::CheckBossCollisions(sf::IntRect p_playerPos)
{
	int enemNum = EnemyManager::Instance().GetBoss()->GetTowerList()->size();
	int bulletNum = BulletManager::Instance().GetPlBulletList()->m_bulletList.size();
	std::vector<CorrespondingEnem> correspondingList = std::vector<CorrespondingEnem>();


	std::vector<int> shouldSkipEnemy = std::vector<int>();

	std::vector<Bullet> bullList = BulletManager::Instance().GetPlBulletList()->m_bulletList;
	std::vector<BossTower>* enemList = EnemyManager::Instance().GetBoss()->GetTowerList();

	for (int i = 0; i < enemNum; i++)
	{
		sf::IntRect enemyRect = EnemyManager::Instance().GetBoss()->GetTowerList()->at(i).GetCollisionBox();
		for (int j = 0; j < bulletNum; j++)
		{
			sf::IntRect bulletRect = BulletManager::Instance().GetPlBulletList()->m_bulletList.at(j).GetCollisionRect();
			if (enemyRect.intersects(bulletRect) && EnemyManager::Instance().GetBoss()->GetTowerList()->at(i).GetAliveState() == Enemy::AliveState::IS_ALIVE)
			{
				bool hasAddedIndex = false;
				for (int k = 0; k < correspondingList.size(); k++)
				{
					if (correspondingList.at(k).m_bull == &BulletManager::Instance().GetPlBulletList()->m_bulletList.at(j))
						hasAddedIndex = true;
					if (correspondingList.at(k).m_enemIndex == i)
						hasAddedIndex = true;
				}
				if (!hasAddedIndex)
					correspondingList.push_back(CorrespondingEnem(&BulletManager::Instance().GetPlBulletList()->m_bulletList.at(j), i));
			}
		}
	}

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
			EnemyManager::Instance().GetBoss()->GetTowerList()->at(correspondingList.at(i).m_enemIndex).ReduceHealth(10);

		else if (correspondingList.at(i).m_bull->GetType() == Bullet::SPREAD)
			EnemyManager::Instance().GetBoss()->GetTowerList()->at(correspondingList.at(i).m_enemIndex).ReduceHealth(1);
	}
}

void CollisionManager::EnemBulletPl(Player * p_player)
{
	int bulletNum = 0;
	sf::IntRect plRect = p_player->GetCollisionBox();
	std::vector<Bullet*> bullList = std::vector<Bullet*>();
	int bullToRemove = -1;

	for (int i = 0; i < BulletManager::Instance().GetBulletList()->size(); i++)
	{
		for (int j = 0; j < BulletManager::Instance().GetBulletList()->at(i)->m_bulletList.size(); j++)
		{
			bullList.push_back(&BulletManager::Instance().GetBulletList()->at(i)->m_bulletList.at(j));
			bulletNum++;
		}
	}

	bool hasBeenHit = false;

	for (int i = 0; i < bulletNum; i++)
	{
		if (bullList.at(i)->GetCollisionRect().intersects(plRect) && !hasBeenHit && !p_player->CheckIfInvulnerable() && p_player->GetAliveState() == Player::ALIVE)
		{
			p_player->SetAliveState(Player::AliveState::PLAYING_ANIM);
			hasBeenHit = true;
			bullToRemove = i;
		}
	}

	if (hasBeenHit == true)
	{
		for (int i = 0; i < BulletManager::Instance().GetBulletList()->size(); i++)
		{
			for (int j = 0; j < BulletManager::Instance().GetBulletList()->at(i)->m_bulletList.size(); j++)
			{
				if (&BulletManager::Instance().GetBulletList()->at(i)->m_bulletList.at(j) == bullList.at(bullToRemove))
				{
					BulletManager::Instance().GetBulletList()->at(i)->m_bulletList.erase(BulletManager::Instance().GetBulletList()->at(i)->m_bulletList.begin() + j);
				}
			}
		}
	}

}