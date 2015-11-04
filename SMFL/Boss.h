#pragma once
#include "BossTower.h"
#include <vector>
#include "WeakSpot.h"
class Boss : public Enemy
{
public:
	Boss();
	~Boss();

	void Init();
	void Update(sf::Vector2f , float p_dt);
	void RemoveVars(){};
	std::vector<sf::Sprite *> GetTextureList();

private:
	std::vector<BossTower> m_towerList;
	std::vector<WeakSpot> m_weakSpots;
	sf::Sprite m_sprite;
	static const sf::Vector2f m_END_POS;
};

