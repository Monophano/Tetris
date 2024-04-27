#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include "tetromino.hpp"

class Grid
{
	public:
		Grid();
		void Add_block_to_map(Tetromino &tetromino);
		void Clear_residus(Tetromino &tetromino);
		bool isValideMove(Tetromino &tetromino);
		void fixe_block(Tetromino &tetromino);
		void Draw(sf::RenderWindow &window);

	private:
		block underMap[20][10];
		block map[20][10];
		const float SIZECELL = 30.0f;
		const int ROW = 20;
		const int COL = 10;
		std::vector<sf::Color> color =
		{
			sf::Color(91,111,143), // vide
			sf::Color::Cyan,
			sf::Color::Yellow,
			sf::Color::Magenta,
			sf::Color(255,127,0), // orange
			sf::Color(23,0,255), // bleu
			sf::Color::Red,
			sf::Color::Green,
			sf::Color::Transparent // transparent
		};
};