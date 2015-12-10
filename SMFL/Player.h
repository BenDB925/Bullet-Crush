#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Joystick.hpp"
#include "BulletGroup.h"
#include "StraightBulletGroup.h"
#include "PlControls.h"
#include "Tower.h"
#include "BulletManager.h"

class Player
{
public:
	// Default Constructor
	Player();
	// Destructor
	~Player();
	// Overloaded Constructor
	Player(sf::Texture&, sf::Vector2f p_pos);


	void Update(float p_deltaTime);

	sf::Vector2f getPosition();
	std::vector<sf::Sprite> getSprite();
	void Shoot(int);

	sf::IntRect GetCollisionBox();

private:

	BulletManager::WeaponType m_weaponType;

	//Jay Added These
	////////////////////////////////////

	float m_angle, m_radiusForAngle;
	float m_delay, m_counterForAnim;


	sf::Vector2f m_position, m_origin, m_velocity;
	sf::Vector2f m_bulletVel;

	int m_currentFrame;
	int m_bulletGroupIndex;


	std::vector<Tower> m_towers;
	std::vector<sf::Sprite> m_allSprites;
	///////////////////////////////////

	sf::Texture * m_tex;
	sf::IntRect m_spriteRect;
	sf::Sprite m_playerSprite;
	sf::Sprite m_playerBullet;
	sf::Sprite m_playerLaser;
	StraightBulletGroup * m_pBulletlist;
	StraightBulletGroup m_bulletList;
	sf::IntRect m_collisionRect;

	static const float m_COLLISIONBOXSIZE;
	static const float m_ANIMTIMER, m_BULLETDELAYTIMER;
	static const float m_SPEED, m_BULLETSPEED;
	static const int m_WIDTH, m_HEIGHT, m_MAXFRAMES, m_MAXTOWERS;
	static const float m_DEGTORAD, m_SPREADANGLE;
	static const int m_BLASTERRADIUS, m_SPREADRADIUS, m_LAZERRADIUS;
};

