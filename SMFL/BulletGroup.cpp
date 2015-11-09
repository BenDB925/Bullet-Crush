#include "stdafx.h"
#include "BulletGroup.h"


BulletGroup::BulletGroup()
{



}


BulletGroup::~BulletGroup()
{
}

void BulletGroup::Update(sf::Time p_deltaTime, sf::Vector2f p_screenDimensions)
{
	for (int i = 0; i < m_bulletList.size(); i++)
	{
		m_bulletList.at(i).Update(p_deltaTime);
		if (m_bulletList.at(i).GetPosition().x > p_screenDimensions.x || m_bulletList.at(i).GetPosition().x < -m_bulletRadius ||
			m_bulletList.at(i).GetPosition().y > p_screenDimensions.y || m_bulletList.at(i).GetPosition().y < -m_bulletRadius)
		{
			m_bulletList.erase(m_bulletList.begin() + i);
		}
	}
}

float BulletGroup::GetRadius()
{
	return m_bulletRadius;
}

bool BulletGroup::ShouldBeDestroyed()
{
	return (m_bulletList.size() == 0);
}

void BulletGroup::SetShouldBeDestroyed(bool p_shouldBeDestroyed)
{
	m_shouldBeDestroyed = true;
}

bool BulletGroup::GetShouldBeDestroyed()
{
	return m_shouldBeDestroyed;
}
