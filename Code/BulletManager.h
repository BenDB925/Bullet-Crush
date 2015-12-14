#pragma once
#include "SFML\System\Time.hpp"
#include "SFML\System\Clock.hpp"
#include <vector>
#include "BulletGroup.h"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "StraightBulletGroup.h"


class BulletManager
{
public:
	enum WeaponType
	{
		BLASTER,
		LAZER,
		SPREAD,
		DEFAULT
	};

	BulletManager();
	~BulletManager();
	void Init(sf::Texture& p_tex);
	void Update(sf::Time p_deltaTime, sf::Vector2f p_screenDimensions);
	void Draw(sf::RenderWindow &p_window);
	void AddSpiral(sf::Vector2f p_point, int p_numColumns, bool p_shouldGoClockwise);
	void AddExplosion(sf::Vector2f p_point, int p_numColumns);
	int AddStraight(StraightBulletGroup *p_pattern, sf::Vector2f p_position, float p_velocity, sf::Vector2f p_direction);
	void PlayerFireBullet(sf::Vector2f p_position, float p_velocity, sf::Vector2f p_direction, BulletManager::WeaponType p_weaponType, int p_radius);
	std::vector<BulletGroup*> *GetBulletList();
	StraightBulletGroup * GetPlBulletList();
	int AddBulletGroup(BulletGroup & p_group);

	void RemoveBulletGroup(BulletGroup *  p_group);

	static BulletManager& Instance();




private:
	std::vector<BulletGroup*> m_bulletGroups;
	StraightBulletGroup m_playerBullets;
	sf::Texture m_textureAtlas;
	sf::Texture * m_pTextureAtlas;
	sf::IntRect m_SPIRAL_TEX_COORDS;
	sf::IntRect m_SPREAD_TEX_COORDS;
	sf::IntRect m_BLASTER_TEX_COORDS;
	sf::IntRect m_LASER_TEX_COORDS;
	sf::IntRect m_DEFAULT_TEX_COORDS;
};

