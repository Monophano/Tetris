#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Grid
{
public:
	Grid();
	void draw(sf::RenderWindow &window);

private:
	const int LINE = 20;
	const int COLUMN = 10;
	int grid1[20][10];
	std::vector<sf::Color> color = {
		sf::Color::Transparent,
		sf::Color::Cyan,
		sf::Color::Yellow,
		sf::Color::Magenta,
		sf::Color::Color(255,165,0),
		sf::Color::Blue,
		sf::Color::Green,
		sf::Color::Red
	};
};