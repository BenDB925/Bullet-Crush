#include "stdafx.h"
#include "Score.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include "SFML\Graphics\Font.hpp"
#include "SFML\Graphics\Text.hpp"

Score::Score() : currentScore(0)
{
}
void Score::Init()
{
	highScores = std::vector<int>();
	highScoresText = std::vector<std::string>();

	std::string line;
	std::ifstream myfile("highscores.txt");
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			std::istringstream iss(line);
			int n;
			while (iss >> n)
			{
				highScores.push_back(n);
			}
		}
		myfile.close();
	}

	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	for (int i = 0; i < highScores.size(); i++)
	{
		highScoresText.push_back(std::to_string(highScores.at(i)));
		highScoresText.at(i) = std::string(9 - highScoresText.at(i).size(), '0') + highScoresText.at(i);
	}
}

Score& Score::Instance()
{
	static Score instance;
	return instance;
}

void Score::UpdateScores()
{
	currentScoreText = std::to_string(currentScore);
	currentScoreText = std::string(9 - currentScoreText.length(), '0') + currentScoreText;

	if (currentScore > highScores.at(0))
		highScoresText.at(0) = currentScoreText;

}

void Score::SortHighScoreTable()
{

}
