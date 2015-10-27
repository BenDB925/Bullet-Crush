#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\System\Time.hpp"
class PlControls
{
public:

	const int m_DEADZONE;
	bool m_leftStickEnabled;
	bool m_rightStickEnabled;
	sf::Vector2f m_leftAnalogStick;
	sf::Vector2f m_rightAnalogStick;
	void Update(sf::Time p_deltaTime);
	sf::Vector2f GetLeftStickAxis();
	sf::Vector2f GetRightStickAxis();
	static PlControls& Instance();
private:
	PlControls();
};


