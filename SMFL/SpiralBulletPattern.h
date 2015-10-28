#include "BulletGroup.h"

class SpiralBulletPattern : public BulletGroup
{
public:
	SpiralBulletPattern(sf::Vector2f p_positon, bool p_shouldGoClockwise, int p_numColumns, int p_radius, float p_velocity, sf::Texture *&p_tex, sf::IntRect p_texCoords);
	~SpiralBulletPattern();

private:
	int m_columnCount = 12;
	float m_velocity;
};

