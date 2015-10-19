#pragma once
#include <vector>
#include "Enemy.h"
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	static EnemyManager& Instance();
	void Init();
	void Update();
	void Draw();

private:
	std::vector<Enemy*> m_enemyList;

	void AddHomingEnem();
};

