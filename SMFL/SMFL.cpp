//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES

#include "Player.h"
#include "BulletManager.h"
#include "PlControls.h"
#include "EnemyManager.h"
#include "Level.h"
#include "CollisionManager.h"
#include "UI.h"



// Game Modes
//////////////////
const byte MAINMENU = 0, GAME = 1, GAMEOVER = 2;
byte gameMode = GAME;

// Variables
//////////////////
sf::Clock myClock;
sf::Time deltaTime;
Player player;
Level level;
sf::Texture m_tex, m_bgTex;
std::vector<sf::Texture> m_backGroundTex;
sf::Vector2f screenDimensions = sf::Vector2f(600, 800);
int fps = 0;

sf::Font font;
sf::Text text;

//////////////////
const byte m_MAXLEVELS = 1;
//////////////////
void Init()
{
	// Ben Have a look at this, need to pass a ref
	// and had to do this shit, myt be wrong.
	// Need a ref because m_tex goes out of scope and you
	// get the white box. This is pointer to a ref I think ?????
	/////////////////////////////////////////////////////
	player = Player(*&m_tex, sf::Vector2f(280, 240));
	level = Level(*&m_backGroundTex, screenDimensions);
	UI::Instance().Init(*&m_tex);

	BulletManager::Instance().Init(*&m_tex);
	EnemyManager::Instance().Init(*&m_tex);
	CollisionManager::Instance().Init();
}
void LoadContent()
{

	// Check that assets are been loaded
	m_tex.loadFromFile("sprite.png");

	for (int i = 0; i < m_MAXLEVELS; i++)
	{
		std::string text = "Level";
		text += std::to_string(i);
		text += ".png";
		m_bgTex.loadFromFile(text);
		m_backGroundTex.push_back(m_bgTex);
	}
}

// UPDATE GAME MODES
//////////////////
void(UpdateMainMenu())
{
}
void(UpdateGame())
{
	level.Update(deltaTime);
	player.Update(deltaTime);
	BulletManager::Instance().Update(deltaTime, screenDimensions);
	EnemyManager::Instance().Update(player.getPosition(), deltaTime.asMilliseconds());
	CollisionManager::Instance().CheckCollisions(player.GetCollisionBox());
}
void(UpdateGameOver())
{
}

// DRAW GAME MODES
//////////////////
void(DrawMainMenu(sf::RenderWindow &p_window))
{
}
void(DrawGame(sf::RenderWindow &p_window))
{
	int maxLevelSprites = level.getSprite().size();
	for (int i = 0; i < maxLevelSprites; i++)
		p_window.draw(level.getSprite().at(i));

	BulletManager::Instance().Draw(p_window);
	EnemyManager::Instance().Draw(p_window);

	int maxPlayerSprites = player.getSprite().size();
	for (int i = 0; i < maxPlayerSprites; i++)
		p_window.draw(player.getSprite().at(i));
	p_window.draw(UI::Instance().getSprite());

}
void(DrawGameOver(sf::RenderWindow &p_window))
{
}


// UPDATE EVENT
/////////////////////////////
void Update()
{
	deltaTime = myClock.getElapsedTime();
	fps = 1.f / deltaTime.asSeconds();

	PlControls::Instance().Update(deltaTime);

	myClock.restart();



	// Update Game Modes
	/////////////////////////////
	switch (gameMode)
	{
	case MAINMENU:
		UpdateMainMenu();
		break;
	case GAME:
		UpdateGame();
		break;
	case GAMEOVER:
		UpdateGameOver();
		break;
	}
}

// DRAW EVENT
/////////////////////////////
void Draw(sf::RenderWindow &p_window)
{
	// Clear Window
	p_window.clear();


	// Update Draw Modes
	/////////////////////////////
	switch (gameMode)
	{
	case MAINMENU:
		DrawMainMenu(p_window);
		break;
	case GAME:
		DrawGame(p_window);
		break;
	case GAMEOVER:
		DrawGameOver(p_window);
		break;
	}

	// Display Window
	p_window.display();
}

////////////////////////////////////////////////////////////
///Entry point of application 
//////////////////////////////////////////////////////////// 
int main()
{

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y, 32), "SFML First Program");
	//load a font
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
	text.setFont(font);
	text.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	text.setPosition(20, 40);
	text.setCharacterSize(20);



	// Load Content
	/////////////////////////////
	LoadContent();

	// Initialize
	/////////////////////////////
	Init();



	// Game Loop
	/////////////////////////////
	while (window.isOpen())
	{


		// Keyboard Events
		/////////////////////////////
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F))
				BulletManager::Instance().AddSpiral(sf::Vector2f(100, 100), (rand() % 16) + 4, (rand() % 2) - 1);

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::G))
				BulletManager::Instance().AddExplosion(sf::Vector2f(100, 100), (rand() % 16) + 4);

			//if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::H))
				//player.Shoot();
		}

		// Update World, Events, Game
		/////////////////////////////
		Update();

		// Draw World, Events, Game
		/////////////////////////////
		Draw(window);
	} 
	return EXIT_SUCCESS;
}



// Joystick Buttons
// (0, 0) - Y
// (0, 1) - A
// (0, 2) - X
// (0, 3) - B
// (0, 4) - Left Bumper
// (0, 5) - Right Bumper
// (0, 6) - Back Bumper
// (0, 7) - Start Bumper
// (0, 8) - Left Analog Press
// (0, 9) - Right Analog Press

// sf::Joystick::X - Left Analog X-Axis
// sf::Joystick::Y - Left Analog Y-Axis
// sf::Joystick::R - Right Analog X-Axis
// sf::Joystick::U - Right Analog Y-Axis
// sf::Joystick::PovX - D-Pad X-Axis
// sf::Joystick::PovY - D-Pad Y-Axis

//// JOYPAD CHECKS
////////////////////////////////////////////////////////////// 
//if (sf::Joystick::isConnected(0))
//{
//	std::cout << "Joypad 1 is connected" << std::endl;
//
//	// Check How Many Buttons Joypad 0 has
//	int buttonCount = sf::Joystick::getButtonCount(0);
//	std::cout << "Button count: " << buttonCount << std::endl;
//}
//else
//std::cout << "Joypad 1 is not connected" << std::endl;