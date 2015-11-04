#include "stdafx.h"
#include "Boss.h"

const sf::Vector2f Boss::m_END_POS = sf::Vector2f(350, 150);

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
	if (m_position.y < m_END_POS.y)
		m_position += m_velocity * p_dt;
	
	for (int i = 0; i < m_towerList.size(); i++)
	{
		m_towerList.at(i).UpdatePosition(m_velocity);
		m_towerList.at(i).Update(p_playerPos, p_dt);
	}
}

void Boss::Init()
{

}

std::vector<sf::Sprite *> Boss::GetTextureList()
{
	std::vector<sf::Sprite *> spriteList;

	for (int i = 0; i < m_towerList.size(); i++)
	{
		spriteList.push_back(m_towerList.at(i).GetTexture());
	}
	for (int i = 0; i < m_weakSpots.size(); i++)
	{
		spriteList.push_back(m_weakSpots.at(i).GetTexture());
	}

	return spriteList;
}
