#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include <utility>
#include "tetromino.hpp"

class Grid
{
	public:
		Grid();

		// positionnement du tetromino dans la grille
		void Add_block_to_map(Tetromino &tetromino);
		void Add_block_to_undermap(Tetromino& tetromino);
		void Clear_residus(Tetromino &tetromino);

		// collision
		bool HasnotReachedStg(Tetromino &tetromino);
		bool HasnotCollidedWithStg(Tetromino &tetromino, bool touche_gauche);
		bool CanRotate(Tetromino &tetromino);

		// gestion de la ligne compl�te
		void destroyLineFull();

		// affichage
		void Draw(sf::RenderWindow &window);
		void DebugDraw();

	private:
		block underMap[21][10];
		block map[21][12];
		const float SIZECELL = 30.0f;
		const int ROW = 20;
		const int COL = 10;
		std::vector<sf::Color> color =
		{
			sf::Color(185, 230, 240), // vide
			sf::Color(5, 201, 245), // cyan
			sf::Color(255,255,0), // yellow
			sf::Color::Magenta,
			sf::Color(245, 89, 5), // orange
			sf::Color(23,0,255), // blue
			sf::Color(255,0,0), // red
			sf::Color(37, 250, 5), // green
			sf::Color::Transparent
		};
};
