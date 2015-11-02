#include "stdafx.h"
#include "Boss.h"


Boss::Boss()
{
	m_towerList = std::vector<BossTower>();
	m_weakSpots = std::vector<WeakSpot>();
	m_velocity = sf::Vector2f(0, 0.01);
}


Boss::~Boss()
{
}

void Boss::Update(sf::Vector2f p_playerPos, float p_dt)
{
	m_position += m_velocity * p_dt;
	for (int i = 0; i < m_towerList.size(); i++)
	{
		m_towerList.at(i).UpdatePosition(m_velocity);
		m_towerList.at(i).Update(p_playerPos, p_dt);
	}
}

void Boss::Draw()
{

}

void Boss::Init()
{

}
