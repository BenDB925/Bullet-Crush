#include "stdafx.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "SFML\Graphics\Rect.hpp"


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

void CollisionManager::CheckCollisions(sf::IntRect p_playerPos)
{
	int enemNum = EnemyManager::Instance().GetEnemyList()->size();

	for (int i = 0; i < enemNum; i++)
	{
		//sf::IntRect enemRect = EnemyManager::Instance().GetEnemyList()->at(i).GetCollisionBox();
		//{
		//}
	}
}
