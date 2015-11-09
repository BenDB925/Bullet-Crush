#include "stdafx.h"
#include "SpiralBulletPattern.h"
#define _USE_MATH_DEFINES
#include <math.h>

float distFormula(sf::Vector2f x, sf::Vector2f y)
{
	float distance, tempx, tempy;
	tempx = (x.x - y.x);
	tempx = pow(tempx, 2.0f);
	tempy = (x.y - y.y);
	tempy = pow(tempy, 2.0f);
	distance = tempx + tempy;
	distance = sqrt(distance);
	return distance;
}

SpiralBulletPattern::SpiralBulletPattern(sf::Vector2f p_position, bool p_shouldGoClockwise, int p_numColumns, int p_radius, float p_velocity, sf::Texture *&p_tex, sf::IntRect p_texCoords)
: m_velocity(p_velocity)
	

{
	m_bulletRadius = p_radius;
	m_bulletList = std::vector<Bullet>();
	m_position = p_position; 
	m_shouldBeDestroyed = true;

	for (int i = 0; i < p_numColumns; i++)
	{
		float randNum = rand() % 1000;
		float currAng = i * M_PI * 2 / p_numColumns + (randNum / 1000);

		sf::Vector2f pointOnCircle = sf::Vector2f(cos(currAng) * m_bulletRadius, sin(currAng) * m_bulletRadius);
		sf::Vector2f velDir = sf::Vector2f(pointOnCircle.y * -1, pointOnCircle.x);
		velDir.x / distFormula(m_position, pointOnCircle);
		velDir.y / distFormula(m_position, pointOnCircle);

		sf::Vector2f vel;
		if (p_shouldGoClockwise)
			vel = velDir * m_velocity;
		else
			vel = -(velDir * m_velocity);

		pointOnCircle = sf::Vector2f(cos(currAng) * m_bulletRadius + m_position.x, sin(currAng) * m_bulletRadius + m_position.y);

		m_bulletList.push_back(Bullet(pointOnCircle, vel, p_tex, p_texCoords));
	}

	int j = 0;
}


SpiralBulletPattern::~SpiralBulletPattern()
{
}
