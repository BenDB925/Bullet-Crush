#pragma once
#include "Enemy.h"
class HomingEnemy : public Enemy
{
public:
	HomingEnemy();
	~HomingEnemy();
	void Init();
	void Update();
	void Draw();
};

