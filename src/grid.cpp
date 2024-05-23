#include "headers/grid.hpp"

Grid::Grid()
{
	for (int ligne = 0; ligne < 21; ligne++)
		for (int colonne = 0; colonne < 12; colonne++)
			map[ligne][colonne] = nothing;

	for (int ligne = 0; ligne < ROW; ligne++)
		for (int colonne = 0; colonne < COL; colonne++)
			underMap[ligne][colonne] = vide;

	for (int colonne = 0; colonne < COL; colonne++) // Initialise Laste Row with a complete line to simplify colision detection on last line
		underMap[20][colonne] = I;

	for (int ligne = 0; ligne < 21; ligne++)
	{
		map[ligne][0] = I;
		map[ligne][11] = I;
	}
}

/* gestion de la ligne compl�te */
void Grid::destroyLineFull()
{
	int nb_block_col = 0;
	for (int ligne = 0; ligne < ROW; ligne++)
	{
		for (int colonne = 0; colonne < COL; colonne++)
		{
			if (underMap[ligne][colonne] != vide)
				nb_block_col++;
			if (nb_block_col == 10)
			{
				// on clear la ligne
				for (int colonne_temp = 0; colonne_temp < COL; colonne_temp++)
					underMap[ligne][colonne_temp] = vide;

				// puis on la d�place tout en haut en d�placant les lignes une apr�s l'autre
				int index = ligne;
				while (index > 0)
				{
					for (int i = 0; i < COL; i++)
						std::swap(underMap[index - 1][i], underMap[index][i]);
					index--;
				}
			}
		}
		nb_block_col = 0;
	}
}

/* Affichage */
void Grid::Draw(sf::RenderWindow &window)
{
	sf::RectangleShape cell(sf::Vector2f(SIZECELL,SIZECELL));

	// Grille du dessous
	for (int ligne = 0; ligne < ROW; ligne++)
	{
		for (int colonne = 0; colonne < COL; colonne++)
		{
			cell.setFillColor(color[underMap[ligne][colonne]]);
			cell.setPosition(colonne * SIZECELL, ligne * SIZECELL);
			window.draw(cell);
		}
	}

	// Grille du dessus
	for (int ligne = 0; ligne < ROW; ligne++)
	{
		for (int colonne = 1; colonne < 11; colonne++)
		{
      		cell.setFillColor(color[map[ligne][colonne]]);
			cell.setPosition((colonne-1) * SIZECELL, ligne * SIZECELL);
			window.draw(cell);
		}
	}
}

void Grid::DebugDraw()
{
	printf("Map :                 	        UnderMap :\n");
	for (int ligne = 0; ligne < 21; ligne++)
	{
		// Map
		for (int colonne = 0; colonne < 12; colonne ++)
			printf("%d ", map[ligne][colonne]);

		printf("	");

		// UnderMap
		for (int colonne = 0; colonne < COL; colonne ++)
			printf("%d ", underMap[ligne][colonne]);

		printf("\n");
	}
	printf("\n");
}
