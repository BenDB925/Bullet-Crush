#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "BulletGroup.h"
#include "SoundManager.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	enum AliveState
	{
		IS_ALIVE,
		IS_PLAYING_ANIMATION,
		IS_DEAD
	};


	virtual void Init() = 0;
	virtual void Update(sf::Vector2f p_playerPos, float p_dt) = 0;
	virtual void RemoveVars() = 0;

	sf::Sprite * GetTexture();
	sf::IntRect GetCollisionBox() { return m_collisionBox; }
	void SetPosition(sf::Vector2f p_pos);
	bool CheckOffScreen(sf::Vector2f p_screenDimensions);
	void DestroyEnemy();
	bool UpdateAnim(float p_dt);
	Enemy::AliveState GetAliveState();
	void ReduceHealth(int p_amt);


protected:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	int m_health;

	sf::IntRect m_collisionBox;
	sf::IntRect m_animBox;

	AliveState m_aliveState;
	int m_currentFrame;
	float m_counterForAnim;

	static const float m_DEATHANIMTIMER;
	static const int m_EXPSIZE;
	static const int m_TEXOFFSETY;
	static const int m_MAXEXPFRAMES;

};