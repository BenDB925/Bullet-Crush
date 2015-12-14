#include "stdafx.h"
#include "BulletManager.h"
#include "SpiralBulletPattern.h"
#include "SFML\Graphics\RenderWindow.hpp"
#include "ExplosionBulletPattern.h"
#include "StraightBulletGroup.h"



BulletManager::BulletManager()
{
	m_SPIRAL_TEX_COORDS = sf::IntRect(0, 109, 10, 10);
	m_SPREAD_TEX_COORDS = sf::IntRect(0, 109, 10, 10);
	m_BLASTER_TEX_COORDS = sf::IntRect(67, 112, 22, 22);
	m_LASER_TEX_COORDS = sf::IntRect(0, 109, 10, 10);
	m_DEFAULT_TEX_COORDS = sf::IntRect(0, 109, 10, 10);
	m_pTextureAtlas = &m_textureAtlas;
}


BulletManager::~BulletManager()
{
}


void BulletManager::Init(sf::Texture& p_tex)
{
	m_textureAtlas = p_tex;
}

void BulletManager::Update(sf::Time p_deltaTime, sf::Vector2f p_screenDimensions)
{
	for (int i = 0; i < m_bulletGroups.size(); i++)
	{
		if (m_bulletGroups.at(i)->m_bulletList.size() > 0)
			m_bulletGroups.at(i)->Update(p_deltaTime, p_screenDimensions);
		// Add back to for loop if breaks
		/////////////////////////////////
		if (m_bulletGroups.at(i)->GetShouldBeDestroyed() && m_bulletGroups.at(i)->ShouldBeDestroyed())
			m_bulletGroups.erase(m_bulletGroups.begin() + i);
	}

	//for (int i = 0; i < m_bulletGroups.size(); i++)
	//{

	//}
	m_playerBullets.Update(p_deltaTime, p_screenDimensions);
}

void BulletManager::Draw(sf::RenderWindow& p_window)
{
	for (int i = 0; i < m_bulletGroups.size(); i++)
	{
		for (int j = 0; j < m_bulletGroups.at(i)->m_bulletList.size(); j++)
		{
			p_window.draw(*m_bulletGroups.at(i)->m_bulletList.at(j).GetTexture());
		}
	}

	for (int j = 0; j < m_playerBullets.m_bulletList.size(); j++)
	{
		p_window.draw(*m_playerBullets.m_bulletList.at(j).GetTexture());
	}
}


BulletManager &BulletManager::Instance()
{
	static BulletManager instance;
	return instance;
}

void BulletManager::AddSpiral(sf::Vector2f p_point, int p_numColumns, bool p_shouldGoClockwise)
{
	SpiralBulletPattern * temp = new SpiralBulletPattern(p_point, p_shouldGoClockwise, p_numColumns, 50, 0.1, m_pTextureAtlas, m_SPIRAL_TEX_COORDS);
	m_bulletGroups.push_back(temp);
	int j = 0;
}

void BulletManager::AddExplosion(sf::Vector2f p_point, int p_numColumns)
{
	m_bulletGroups.push_back(new ExplosionBulletPattern(p_point, p_numColumns, 50, 4, m_pTextureAtlas, m_SPIRAL_TEX_COORDS));
}

int BulletManager::AddStraight(StraightBulletGroup *p_pattern, sf::Vector2f p_position, float p_velocity, sf::Vector2f p_direction)
{
	return int(p_pattern->AddBullet(p_position, p_velocity, p_direction, m_pTextureAtlas, m_DEFAULT_TEX_COORDS));
}

void BulletManager::PlayerFireBullet(sf::Vector2f p_position, float p_velocity, sf::Vector2f p_direction, BulletManager::WeaponType p_weaponType, int p_radius)
{
	if (p_weaponType == WeaponType::BLASTER)
		m_playerBullets.AddBullet(p_position, p_velocity, p_direction, m_pTextureAtlas, m_BLASTER_TEX_COORDS, p_radius, Bullet::BulletType::BLASTER);
	else if (p_weaponType == WeaponType::LAZER)
		m_playerBullets.AddBullet(p_position, p_velocity, p_direction, m_pTextureAtlas, m_LASER_TEX_COORDS, p_radius, Bullet::BulletType::LAZER);
	else if (p_weaponType == WeaponType::SPREAD)
		m_playerBullets.AddBullet(p_position, p_velocity, p_direction, m_pTextureAtlas, m_SPREAD_TEX_COORDS, p_radius, Bullet::BulletType::SPREAD);
}

std::vector<BulletGroup*> * BulletManager::GetBulletList()
{
	return &m_bulletGroups;
}

StraightBulletGroup * BulletManager::GetPlBulletList()
{
	return &m_playerBullets;
}

int BulletManager::AddBulletGroup(BulletGroup & p_group)
{
	m_bulletGroups.push_back(&p_group);
	return (int)m_bulletGroups.size() - 1;
}

void BulletManager::RemoveBulletGroup(BulletGroup * p_group)
{
	for (int i = 0; i < m_bulletGroups.size(); i++)
	{
		if (*&m_bulletGroups.at(i) == *&p_group)
		{
			m_bulletGroups.at(i)->SetShouldBeDestroyed(true);
		}
	}
}

