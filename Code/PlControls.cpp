#include "stdafx.h"
#include "PlControls.h"
#include "SFML\Window\Joystick.hpp"


PlControls::PlControls() :
m_DEADZONEA(15),
m_DEADZONEB(50),
m_counter(0),
m_buttonCount(sf::Joystick::getButtonCount(0))
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



		m_anyKeyPressed = sf::Joystick::isButtonPressed(0, 0);


	m_rightBumperPressed = sf::Joystick::isButtonPressed(0, 5);
	m_leftBumperPressed = sf::Joystick::isButtonPressed(0, 4);

	m_leftAnalogStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
	m_rightAnalogStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::U), sf::Joystick::getAxisPosition(0, sf::Joystick::R));

	// Updates Left Analog Stick
	////////////////////////////////
	if (m_leftAnalogStick.x > m_DEADZONEA || m_leftAnalogStick.x < -m_DEADZONEA || m_leftAnalogStick.y > m_DEADZONEA || m_leftAnalogStick.y < -m_DEADZONEA)
	{
		m_leftStickEnabled = true;
		m_leftAnalogAngle = atan2(m_leftAnalogStick.y, m_leftAnalogStick.x);
	}
	else
		m_leftStickEnabled = false;

	// Updates Right Analog Stick
	////////////////////////////////
	if (m_rightAnalogStick.x > m_DEADZONEB || m_rightAnalogStick.x < -m_DEADZONEB || m_rightAnalogStick.y > m_DEADZONEB || m_rightAnalogStick.y < -m_DEADZONEB)
	{
		m_rightStickEnabled = true;
		m_rightAnalogAngle = atan2(m_rightAnalogStick.y, m_rightAnalogStick.x);
	}
	else
		m_rightStickEnabled = false;
}

bool PlControls::GetRightBumperBtn()
{
	return m_rightBumperPressed;
}
bool PlControls::GetLeftBumperBtn()
{
	return m_leftBumperPressed;
}

bool PlControls::GetAnyKey()
{
	return m_anyKeyPressed;
}
