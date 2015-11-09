#include "stdafx.h"
#include "Boss.h"

const sf::Vector2f Boss::m_END_POS = sf::Vector2f(350, 100);
const sf::Vector2f Boss::m_START_POS = sf::Vector2f(75, -250);

const sf::Vector2f Boss::m_TOWER_POS_1 = sf::Vector2f(177, -150);
const sf::Vector2f Boss::m_TOWER_POS_2 = sf::Vector2f(290, -70);
const sf::Vector2f Boss::m_TOWER_POS_3 = sf::Vector2f(402, -150);

const sf::IntRect Boss::m_TOWER_TEX_RECT = sf::IntRect(68, 134, 20, 20);

const sf::IntRect Boss::m_BOSS_SIZE = sf::IntRect(50, 50, 400, 100);



Boss::Boss(sf::Texture * p_tex, sf::IntRect p_texRect)
{
	m_sprite = sf::Sprite(*p_tex);
	m_sprite.setTextureRect(p_texRect);
	
	m_position = m_START_POS;
	m_sprite.setPosition(m_START_POS);

	m_velocity = sf::Vector2f(0, 0.0001);

	m_towerList = std::vector<BossTower>();
	m_weakSpots = std::vector<WeakSpot>();

	m_towerList.push_back(BossTower(m_TOWER_POS_1, p_tex, m_TOWER_TEX_RECT));
	m_towerList.push_back(BossTower(m_TOWER_POS_2, p_tex, m_TOWER_TEX_RECT));
	m_towerList.push_back(BossTower(m_TOWER_POS_3, p_tex, m_TOWER_TEX_RECT));
}

Boss::Boss()
{

}


Boss::~Boss()
{
}

void Boss::Update(sf::Vector2f p_playerPos, float p_dt)
{
	if (m_position.y < m_END_POS.y)
	{
		m_position += m_velocity * p_dt;
		for (int i = 0; i < m_towerList.size(); i++)
		{
			m_towerList.at(i).UpdatePosition(m_velocity * p_dt);
		}
	}

	m_sprite.setPosition(m_position);
	
	for (int i = 0; i < m_towerList.size(); i++)
	{
		m_towerList.at(i).Update(p_playerPos, p_dt);
	}
}

void Boss::Init()
{

}

std::vector<sf::Sprite> Boss::GetTextureList()
{
	std::vector<sf::Sprite> spriteList;

	spriteList.push_back(m_sprite);

	for (int i = 0; i < m_towerList.size(); i++)
	{
		spriteList.push_back(*m_towerList.at(i).GetTexture());
	}
	for (int i = 0; i < m_weakSpots.size(); i++)
	{
		spriteList.push_back(*m_weakSpots.at(i).GetTexture());
	}

	return spriteList;
}

