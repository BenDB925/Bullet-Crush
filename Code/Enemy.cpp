#include "stdafx.h"
#include "Enemy.h"
#include "Score.h"

const float Enemy::m_DEATHANIMTIMER = 30000;
const int Enemy::m_MAXEXPFRAMES = 7;
const int Enemy::m_EXPSIZE = 40;
const int Enemy::m_TEXOFFSETY = 156;

Enemy::Enemy() :
m_aliveState(Enemy::AliveState::IS_ALIVE), m_currentFrame(0), m_counterForAnim(0)
{
}


Enemy::~Enemy()
{
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
	Score::Instance().currentScore += 10;
	m_aliveState = Enemy::AliveState::IS_PLAYING_ANIMATION;
	SoundManager::Instance().PlaySoundEffect3D(m_position);
}

bool Enemy::UpdateAnim(float p_dt)
{
	if (m_aliveState == Enemy::AliveState::IS_PLAYING_ANIMATION)
	{
		m_counterForAnim += p_dt;

		if (m_counterForAnim > m_DEATHANIMTIMER)
		{
			m_currentFrame++;
			m_counterForAnim = 0;
			if (m_currentFrame > m_MAXEXPFRAMES)
				m_aliveState = Enemy::AliveState::IS_DEAD;
		}
		m_animBox = sf::IntRect(m_EXPSIZE * m_currentFrame, m_TEXOFFSETY, m_EXPSIZE, m_EXPSIZE);
		m_sprite.setTextureRect(m_animBox);
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

void Enemy::ReduceHealth(int p_amt)
{
	m_health -= p_amt;
	if (m_health < 0)
		DestroyEnemy();
}