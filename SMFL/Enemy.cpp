#include "stdafx.h"
#include "Enemy.h"

const float Enemy::m_DEATHANIMTIMER = 30000;
const int Enemy::m_MAXEXPFRAMES = 7;
const int Enemy::m_EXPSIZE = 40;
const int Enemy::m_TEXOFFSETY = 156;

Enemy::Enemy() : 
m_aliveState(Enemy::AliveState::IS_ALIVE)
{
}


Enemy::~Enemy()
{
	delete(m_bulletGroup);
}

sf::Sprite * Enemy::GetTexture()
{
	return &m_sprite;
}

void Enemy::SetPosition(sf::Vector2f p_pos)
{
	m_position = p_pos;
}

bool Enemy::CheckOffScreen(sf::Vector2f p_screenDimensions)
{
	if (m_position.x > p_screenDimensions.x || m_position.x < -m_collisionBox.width / 2 ||
		m_position.y > p_screenDimensions.y)
	{
		return true;

	}
	else
		return false;
}

void Enemy::DestroyEnemy()
{
	m_aliveState = Enemy::AliveState::IS_PLAYING_ANIMATION;
}

bool Enemy::UpdateAnim(float p_dt)
{
	if (m_aliveState == Enemy::AliveState::IS_PLAYING_ANIMATION)
	{
		// Animate my Helicopter
		////////////////////////////
		m_counterForAnim += p_dt;

		if (m_counterForAnim > m_DEATHANIMTIMER)
		{
			m_currentFrame++;
			m_counterForAnim = 0;
			if (m_currentFrame > m_MAXEXPFRAMES)
				m_aliveState = Enemy::AliveState::IS_DEAD;
		}
		m_collisionBox = sf::IntRect(m_EXPSIZE * m_currentFrame, m_TEXOFFSETY, m_EXPSIZE, m_EXPSIZE);
		m_sprite.setTextureRect(m_collisionBox);
		return true;
	}
	else if (m_aliveState == Enemy::AliveState::IS_DEAD)
		return false;

	return true;
}

Enemy::AliveState Enemy::GetAliveState()
{
	return m_aliveState;
}
