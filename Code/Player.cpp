#include "stdafx.h"
#include "Player.h"
#include "BulletManager.h"

const float Player::m_ANIMTIMER = 30000;
const float Player::m_BULLETDELAYTIMER = 80000;
const float Player::m_SPEED = 0.000005;
const float Player::m_BULLETSPEED = 2.1;
const float Player::m_DEGTORAD = acos(-1) / 180;
const float Player::m_SPREADANGLE = 10;

const int Player::m_MAXTOWERS = 2;
const int Player::m_MAXFRAMES = 5;
const int Player::m_WIDTH = 64;
const int Player::m_HEIGHT = 78;
const float Player::m_COLLISIONBOXWIDTH = 25;
const float Player::m_COLLISIONBOXHEIGHT = 25;


const int Player::m_DEATHANIMTIMER = 90000;
const int Player::m_MAXEXPFRAMES = 7;
const int Player::m_EXPSIZE = 40;
const int Player::m_FLASH_TIMER = 20000;


const int Player::m_TEXOFFSETY = 156;


const int Player::m_INVULNERABLE_LENGTH = 2500000;

const int Player::m_BLASTERRADIUS = 11;
const int Player::m_SPREADRADIUS = 5;
const int Player::m_LAZERRADIUS = 64;

const int Player::m_MAX_LIVES = 5;

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
m_counterForHeliAnim(0),
m_lives(m_MAX_LIVES),
m_aliveState(AliveState::ALIVE),
m_isInvulnerable(false),
m_invulnerableCounter(0),
m_counterFordeathAnim(0),
m_flashCounter(0),
m_shouldBeHidden(false),
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
}
// Destructor
///////////////////////////
Player::~Player()
{
}

void Player::Update(float p_deltaTime)
{
	switch (m_aliveState)
	{
	case AliveState::ALIVE:
		UpdateAlive(p_deltaTime);
		break;

	case AliveState::DEAD:
		UpdateDead(p_deltaTime);
		break;

	case AliveState::PLAYING_ANIM:
		UpdateAnim(p_deltaTime);
		break;
	}
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

void Player::SetAliveState(AliveState p_state)
{
	m_currentFrame = 0;
	m_aliveState = p_state;
}

void Player::UpdateAlive(float p_dt)
{
	if (m_isInvulnerable)
	{
		if (m_flashCounter > m_FLASH_TIMER)
		{
			m_flashCounter = 0;
			m_shouldBeHidden = !m_shouldBeHidden;
		}
		else
			m_flashCounter += p_dt;


		if (m_invulnerableCounter > m_INVULNERABLE_LENGTH)
		{
			m_invulnerableCounter = 0;
			m_isInvulnerable = false;
		}
		else
		{
			m_invulnerableCounter += p_dt;
		}
	}
	else
		m_shouldBeHidden = false;

	if (PlControls::Instance().GetRightBumperBtn())
		m_weaponType = BulletManager::WeaponType::SPREAD;
	else if (PlControls::Instance().GetLeftBumperBtn())
		m_weaponType = BulletManager::WeaponType::BLASTER;

	// Animate my Helicopter
	////////////////////////////
	m_counterForHeliAnim += p_dt;
	m_delay -= p_dt;

	if (m_counterForHeliAnim > m_ANIMTIMER)
	{
		m_currentFrame++;
		m_counterForHeliAnim = 0;
		if (m_currentFrame > m_MAXFRAMES)
			m_currentFrame = 0;
	}
	m_spriteRect = sf::IntRect(m_WIDTH * m_currentFrame, 0, m_WIDTH, m_HEIGHT);
	m_playerSprite.setTextureRect(m_spriteRect);



	//Check state of joystick Analog A
	/////////////////////////////////////////////
	if (PlControls::Instance().m_leftStickEnabled)
	{
		m_velocity = PlControls::Instance().GetLeftStickAxis() * m_SPEED * p_dt;
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

	m_collisionRect = sf::IntRect(m_position.x + (m_COLLISIONBOXWIDTH / 5) * 4, m_position.y + (m_COLLISIONBOXHEIGHT)* 1.2, m_COLLISIONBOXWIDTH, m_COLLISIONBOXHEIGHT);
}

void Player::UpdateDead(float p_dt)
{
	m_lives -= 1;
	m_position = sf::Vector2f(280, 600);
	m_origin = sf::Vector2f(m_position.x + m_WIDTH * 0.5f, m_position.y + m_HEIGHT * 0.5f);
	m_aliveState = AliveState::ALIVE;
	m_isInvulnerable = true;

	sf::Sprite temp;
	temp.setTexture(*m_tex);
	temp.setTextureRect(sf::IntRect(68, 134, 20, 20));
	m_towers.clear();
	m_towers.push_back(Tower(temp, sf::Vector2f(m_position.x - 20, m_position.y + 40), true));
	m_towers.push_back(Tower(temp, sf::Vector2f(m_position.x + 64, m_position.y + 40), true));


	m_playerSprite.setPosition(m_position);
	m_collisionRect = sf::IntRect(m_position.x + (m_COLLISIONBOXWIDTH / 5) * 4, m_position.y + (m_COLLISIONBOXHEIGHT)* 1.2, m_COLLISIONBOXWIDTH, m_COLLISIONBOXHEIGHT);
}

int Player::GetLivesNum()
{
	return m_lives;
}

void Player::UpdateAnim(float p_dt)
{
	m_counterFordeathAnim += p_dt;

	if (m_counterFordeathAnim > m_DEATHANIMTIMER)
	{
		m_currentFrame++;
		m_counterFordeathAnim = 0;
		if (m_currentFrame > m_MAXEXPFRAMES)
		{
			m_aliveState = AliveState::DEAD;
			m_currentFrame = 0;
		}
	}
	m_animBox = sf::IntRect(m_EXPSIZE * m_currentFrame, m_TEXOFFSETY, m_EXPSIZE, m_EXPSIZE);
	m_playerSprite.setTextureRect(m_animBox);
	m_playerSprite.setPosition(m_position.x + m_playerSprite.getGlobalBounds().width / 3, m_position.y + m_playerSprite.getGlobalBounds().height / 3);
}

bool Player::CheckIfInvulnerable()
{
	return m_isInvulnerable;
}

bool Player::CheckIfHidden()
{
	return m_shouldBeHidden;
}

Player::AliveState Player::GetAliveState()
{
	return m_aliveState;
}
