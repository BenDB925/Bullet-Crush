#include "stdafx.h"
#include "Player.h"
#include "BulletManager.h"


const float Player::m_ANIMTIMER = 30000;
const float Player::m_BULLETDELAYTIMER = 200;
const float Player::m_SPEED = 3;
const float Player::m_BULLETSPEED = 3;
const int Player::m_MAXFRAMES = 5;
const int Player::m_WIDTH = 64;
const int Player::m_HEIGHT = 78;

// Default Constructor
///////////////////////////
Player::Player()
{
}
// Overloaded Constructor
///////////////////////////
Player::Player(sf::Texture& p_tex, sf::Vector2f p_pos) :
m_tex(&p_tex),
m_position(p_pos),
m_delay(0),
m_currentFrame(0),
m_counterForAnim(0),
m_weaponType(BulletManager::WeaponType::SPREAD)
{

	m_playerSprite.setTexture(p_tex);
	m_playerSprite.setTextureRect(sf::IntRect(0, 0, m_WIDTH, m_HEIGHT));
	m_playerSprite.setPosition(m_position);



	m_velocity = sf::Vector2f(0, 0);


	// Setting Up Towers
	///////////////////////////////
	sf::Sprite temp;
	temp.setTexture(p_tex);
	temp.setTextureRect(sf::IntRect(68, 134, 20, 20));
	m_towers.push_back(Tower(temp, sf::Vector2f(m_position.x - 20, m_position.y + 40)));
	m_towers.push_back(Tower(temp, sf::Vector2f(m_position.x + 64, m_position.y + 40)));
}
// Destructor
///////////////////////////
Player::~Player()
{
}

void Player::Update(sf::Time p_deltaTime)
{

	// Animate my Helicopter
	m_counterForAnim += p_deltaTime.asMicroseconds();

	if (m_counterForAnim > m_ANIMTIMER)
	{
		m_currentFrame++;
		m_counterForAnim = 0;
		if (m_currentFrame > m_MAXFRAMES)
			m_currentFrame = 0;
	}
	m_spriteRect = sf::IntRect(m_WIDTH * m_currentFrame, 0, m_WIDTH, m_HEIGHT);
	m_playerSprite.setTextureRect(m_spriteRect);

	m_delay -= 1;

	//Check state of joystick Analog A
	/////////////////////////////////////////////
	if (PlControls::Instance().m_leftStickEnabled)
	{
		m_velocity = PlControls::Instance().GetLeftStickAxis() * m_SPEED * p_deltaTime.asSeconds();
		m_position += m_velocity;
		m_playerSprite.setPosition(m_position);

		for (int i = 0; i < 2; i++)
			m_towers.at(i).Update(m_velocity);

	}
	if (PlControls::Instance().m_rightStickEnabled)
	{
		if (m_delay <= 0)
		{
			for (int i = 0; i < 2; i++)
			{
				m_angle = atan2(PlControls::Instance().GetRightStickAxis().y, PlControls::Instance().GetRightStickAxis().x);
				Shoot(i);
			}
			m_delay = m_BULLETDELAYTIMER;
		}
	}
}


void Player::Shoot(int i)
{
	if (m_weaponType == BulletManager::WeaponType::SPREAD)
	{
		for (int j = -10; j < 20; j += 10)
		{
			float temp = j * acos(-1) / 180;
			m_bulletVel = sf::Vector2f(cos(m_angle + temp), sin(m_angle + temp));

			sf::Vector2f position = m_towers.at(i).getOrigin() + (m_bulletVel * 5.0f);
			sf::Vector2f direction = m_bulletVel * m_BULLETSPEED;
			BulletManager::Instance().PlayerFireBullet(position, m_BULLETSPEED, direction, BulletManager::SPREAD);
		}
	}
	else if (m_weaponType == BulletManager::WeaponType::BLASTER)
	{
		m_bulletVel = sf::Vector2f(cos(m_angle), sin(m_angle));
		sf::Vector2f position = m_towers.at(i).getOrigin() + (m_bulletVel * 5.0f);
		sf::Vector2f direction = m_bulletVel * m_BULLETSPEED;
		BulletManager::Instance().PlayerFireBullet(position, m_BULLETSPEED, direction, BulletManager::BLASTER);
	}
}


// Getters
///////////////////////////
sf::Vector2f Player::getPosition()
{
	return m_position;
}

sf::Sprite Player::getSprite()
{
	return m_playerSprite;
}

sf::Sprite Player::getTowerSprite(int i)
{
	return m_towers.at(i).getSprite();
}

// Setters
///////////////////////////