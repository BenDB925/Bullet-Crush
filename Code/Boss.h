#pragma once
#include "BossTower.h"
#include <vector>
#include "WeakSpot.h"
class Boss
{
public:
	Boss();
	Boss(sf::Texture * p_tex, sf::IntRect p_texRect);
	~Boss();

	void Init();
	void Update(sf::Vector2f, float p_dt);
	void RemoveVars(){};
	std::vector<sf::Sprite> GetTextureList();
	std::vector<BossTower> * GetTowerList();
	bool CheckIfDefeated();

private:
	std::vector<BossTower> m_towerList;
	std::vector<WeakSpot> m_weakSpots;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	static const sf::Vector2f m_END_POS;
	static const sf::Vector2f m_START_POS;

	static const sf::Vector2f m_TOWER_POS_1;
	static const sf::Vector2f m_TOWER_POS_2;
	static const sf::Vector2f m_TOWER_POS_3;

	static const sf::IntRect m_TOWER_COLL_BOX_1;
	static const sf::IntRect m_TOWER_COLL_BOX_2;
	static const sf::IntRect m_TOWER_COLL_BOX_3;

	static const sf::IntRect m_TOWER_TEX_RECT;

	static const sf::IntRect m_BOSS_SIZE;
};

