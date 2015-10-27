#include "stdafx.h"
#include "PlControls.h"
#include "SFML\Window\Joystick.hpp"


PlControls::PlControls()
:m_DEADZONE(15)
{

}

sf::Vector2f PlControls::GetLeftStickAxis()
{
	return m_leftAnalogStick;
}

sf::Vector2f PlControls::GetRightStickAxis()
{
	return m_rightAnalogStick;
}

PlControls& PlControls::Instance()
{
	static PlControls instance;
	return instance;
}

void PlControls::Update(sf::Time p_deltaTime)
{
	m_leftAnalogStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
	m_rightAnalogStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::U), sf::Joystick::getAxisPosition(0, sf::Joystick::R));

	// Updates Left Analog Stick
	////////////////////////////////
	if (m_leftAnalogStick.x > m_DEADZONE || m_leftAnalogStick.x < -m_DEADZONE || m_leftAnalogStick.y > m_DEADZONE || m_leftAnalogStick.y < -m_DEADZONE)
		m_leftStickEnabled = true;
	else
		m_leftStickEnabled = false;

	// Updates Right Analog Stick
	////////////////////////////////
	if (m_rightAnalogStick.x > m_DEADZONE || m_rightAnalogStick.x < -m_DEADZONE || m_rightAnalogStick.y > m_DEADZONE || m_rightAnalogStick.y < -m_DEADZONE)
		m_rightStickEnabled = true;
	else
		m_rightStickEnabled = false;
}
