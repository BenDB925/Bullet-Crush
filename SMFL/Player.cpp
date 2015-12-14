#include "stdafx.h"
#include "Player.h"
#include "BulletManager.h"

const float Player::m_ANIMTIMER = 30000;
const float Player::m_BULLETDELAYTIMER = 80000;
const float Player::m_SPEED = 0.000005;
const float Player::m_BULLETSPEED = 2.1;
const float Player::m_DEGTORAD = acos(-1) / 180;
const float Player::m_SPREADANGLE = 10;

const int Player::m_MAXTOWERS = 3;
const int Player::m_MAXFRAMES = 5;
const int Player::m_WIDTH = 64;
const int Player::m_HEIGHT = 78;
const float Player::m_COLLISIONBOXSIZE = 50;

const int Player::m_BLASTERRADIUS = 11;
const int Player::m_SPREADRADIUS = 5;
const int Player::m_LAZERRADIUS = 64;

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
m_weaponType(BulletManager::WeaponType::BLASTER)
{

	m_origin = sf::Vector2f(m_position.x + m_WIDTH * 0.5f, m_position.y + m_HEIGHT * 0.5f);
	m_playerSprite.setTexture(p_tex);
	m_playerSprite.setTextureRect(sf::IntRect(0, 0, m_WIDTH, m_HEIGHT));
	m_playerSprite.setPosition(m_position);

	// Setting Up Towers
	///////////////////////////////
	sf::Sprite temp;
	temp.setTexture(p_tex);
	temp.setTextureRect(sf::IntRect(68, 134, 20, 20));

	m_towers.push_back(Tower(temp, sf::Vector2f(m_position.x - 20, m_position.y + 40), true));
	m_towers.push_back(Tower(temp, sf::Vector2f(m_position.x + 64, m_position.y + 40), true));
	// Test
	////////////
	m_towers.push_back(Tower(temp, sf::Vector2f(m_position.x + 64, m_position.y + 40), false));
}
// Destructor
///////////////////////////
Player::~Player()
{
}

void Player::Update(float p_deltaTime)
{

	if (PlControls::Instance().GetRightBumperBtn())
		m_weaponType = BulletManager::WeaponType::SPREAD;
	else if (PlControls::Instance().GetLeftBumperBtn())
		m_weaponType = BulletManager::WeaponType::BLASTER;

	// Animate my Helicopter
	////////////////////////////
	m_counterForAnim += p_deltaTime;
	m_delay -= p_deltaTime;

	if (m_counterForAnim > m_ANIMTIMER)
	{
		m_currentFrame++;
		m_counterForAnim = 0;
		if (m_currentFrame > m_MAXFRAMES)
			m_currentFrame = 0;
	}
	m_spriteRect = sf::IntRect(m_WIDTH * m_currentFrame, 0, m_WIDTH, m_HEIGHT);
	m_playerSprite.setTextureRect(m_spriteRect);



	//Check state of joystick Analog A
	/////////////////////////////////////////////
	if (PlControls::Instance().m_leftStickEnabled)
	{
		m_velocity = PlControls::Instance().GetLeftStickAxis() * m_SPEED * p_deltaTime;
		m_position += m_velocity;
		m_playerSprite.setPosition(m_position);
		m_origin = sf::Vector2f(m_position.x + m_WIDTH * 0.5f, m_position.y + m_HEIGHT * 0.5f);

		for (int towerNo = 0; towerNo < m_MAXTOWERS; towerNo++)
		{
			if (m_towers.at(towerNo).getAlive())
				m_towers.at(towerNo).Update(m_velocity);
		}
	}
	//Check state of joystick Analog B
	/////////////////////////////////////////////
	if (PlControls::Instance().m_rightStickEnabled)
	{
		if (m_delay < 0)
		{
			for (int towerNo = 0; towerNo < m_MAXTOWERS; towerNo++)
				if (m_towers.at(towerNo).getAlive())
					Shoot(towerNo);
			m_delay = m_BULLETDELAYTIMER;
		}
	}

	m_collisionRect = sf::IntRect(m_position.x - m_COLLISIONBOXSIZE / 2, m_position.y - m_COLLISIONBOXSIZE / 2, m_COLLISIONBOXSIZE, m_COLLISIONBOXSIZE);
}


void Player::Shoot(int towerNo)
{
	if (m_weaponType == BulletManager::WeaponType::SPREAD)
	{
		for (int bulletNo = -m_SPREADANGLE; bulletNo < m_SPREADANGLE + m_SPREADANGLE; bulletNo += m_SPREADANGLE)
		{
			float temp = bulletNo * m_DEGTORAD;
			m_bulletVel = sf::Vector2f(cos(PlControls::Instance().m_rightAnalogAngle + temp), sin(PlControls::Instance().m_rightAnalogAngle + temp));

			sf::Vector2f position = m_towers.at(towerNo).getOrigin(m_SPREADRADIUS) + (m_bulletVel * 5.0f);
			sf::Vector2f direction = m_bulletVel * m_BULLETSPEED;
			BulletManager::Instance().PlayerFireBullet(position, m_BULLETSPEED, direction, BulletManager::SPREAD, 5);
		}
	}
	else if (m_weaponType == BulletManager::WeaponType::BLASTER)
	{

		sf::Vector2f position = m_towers.at(towerNo).getOrigin(m_BLASTERRADIUS);
		m_bulletVel = sf::Vector2f(cos(PlControls::Instance().m_rightAnalogAngle), sin(PlControls::Instance().m_rightAnalogAngle));

		sf::Vector2f direction = m_bulletVel * m_BULLETSPEED;
		BulletManager::Instance().PlayerFireBullet(position, m_BULLETSPEED, direction, BulletManager::BLASTER, m_BLASTERRADIUS);
	}
	else if (m_weaponType == BulletManager::WeaponType::LAZER)
	{
		// Radius of the imaginary circle where the bullets will meet
		////////////////////////////////////
		float magicCircle = 400;

		sf::Vector2f newAngle = sf::Vector2f(cos(PlControls::Instance().m_rightAnalogAngle) * magicCircle + m_origin.x, sin(PlControls::Instance().m_rightAnalogAngle) * magicCircle + m_origin.y);
		sf::Vector2f position = m_towers.at(towerNo).getOrigin(m_LAZERRADIUS) + (m_bulletVel * 5.0f);

		float temp2 = atan2(newAngle.y - position.y, newAngle.x - position.x);
		m_bulletVel = sf::Vector2f(cos(temp2), sin(temp2));

		sf::Vector2f direction = m_bulletVel * m_BULLETSPEED;
		BulletManager::Instance().PlayerFireBullet(position, m_BULLETSPEED, direction, BulletManager::LAZER, 5);
	}
	else if (m_weaponType == BulletManager::WeaponType::DEFAULT)
	{

		sf::Vector2f position = m_towers.at(towerNo).getOrigin(m_BLASTERRADIUS);
		m_bulletVel = sf::Vector2f(cos(PlControls::Instance().m_rightAnalogAngle), sin(PlControls::Instance().m_rightAnalogAngle));

		sf::Vector2f direction = m_bulletVel * m_BULLETSPEED;
		BulletManager::Instance().PlayerFireBullet(position, m_BULLETSPEED, direction, BulletManager::DEFAULT, m_SPREADRADIUS);
	}
}


// Getters
///////////////////////////
sf::Vector2f Player::getPosition()
{
	return m_position;
}
sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}

std::vector<sf::Sprite> Player::getSprite()
{
	std::vector<sf::Sprite> sprites;
	sprites.push_back(m_playerSprite);

	for (int i = 0; i < m_MAXTOWERS; i++)
		if (m_towers.at(i).getAlive())
			sprites.push_back(m_towers.at(i).getSprite());


	return sprites;
}
sf::IntRect Player::GetCollisionBox()
{
	return m_collisionRect;
}
// Setters
///////////////////////////