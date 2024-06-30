#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include "globals.hpp"

class Grid
{
	public:
		Grid();
		~Grid();
		//block underMap[21][10];
		//block map[21][12];
		block **underMap;
		block **map;

		// gestion des grilles
		void destroyLineFull();
		int NbLineFull();

		// affichage
		void Draw(sf::RenderWindow &window);
		void DebugDraw(int nblines, int nbcols, block **grille);

	private:
		void Draw_Grid(int nblines, int nbcols, int decalage, block **grille, sf::RenderWindow &window);
		const float SIZECELL = 30.0f;
		std::vector<sf::Color> color =
		{
			sf::Color(5, 201, 245), // cyan
			sf::Color(255,255,0), // yellow
			sf::Color::Magenta,
			sf::Color(245, 89, 5), // orange
			sf::Color(23,0,255), // blue
			sf::Color(255,0,0), // red
			sf::Color(37, 250, 5), // green
			sf::Color(185, 230, 240), // vide
			sf::Color::Transparent
		};
};
