#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include "game.hpp"
#include "globals.hpp"

class Grid
{
	public:
		Grid();
		block underMap[21][10];
		block map[21][12];

		/// @brief Compte les lignes complètes
		/// @return nb_ligne_complete : int
		int nb_line_full();

		// gestion de la ligne complète
		void destroyLineFull();

		// affichage
		void Draw(sf::RenderWindow &window);
		void DebugDraw();

	private:
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
