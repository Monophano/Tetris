#include "headers/grid.hpp"

Grid::Grid()
{
	// création des listes
	map = new block* [21];
	underMap = new block* [21];

	for (int i = 0; i < 21; i++)
	{
		map[i] = new block [12];
		underMap[i] = new block [10];
	}

	// remplissage
	for (int ligne = 0; ligne < 21; ligne++)
	for (int colonne = 0; colonne < 12; colonne++)
		map[ligne][colonne] = nothing;

	for (int ligne = 0; ligne < 21; ligne++)
	{
		map[ligne][0] = I;
		map[ligne][11] = I;
	}

	for (int ligne = 0; ligne < ROW; ligne++)
	for (int colonne = 0; colonne < COL; colonne++)
		underMap[ligne][colonne] = vide;

	for (int colonne = 0; colonne < COL; colonne++) // Initialise Laste Row with a complete line to simplify colision detection on last line
		underMap[20][colonne] = I;
}

Grid::~Grid()
{
	for (int i = 0; i < 21; i++)
	{
		delete map[i];
		delete underMap[i];
	}

	delete map;
	delete underMap;
}

/* gestion des grilles */
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

int Grid::NbLineFull()
{
	// compte le nombre de ligne à détruire
    int nb_block_col = 0;
    int nb_line_full = 0;
	for (int ligne = 0; ligne < ROW; ligne++)
	{
		for (int colonne = 0; colonne < COL; colonne++)
		{
			if (underMap[ligne][colonne] != vide)
				nb_block_col++;
			if (nb_block_col == 10)
			{
                nb_line_full++;
			}
		}
		nb_block_col = 0;
	}
	return nb_line_full;
}

/* Affichage */
void Grid::Draw(sf::RenderWindow &window)
{
	/*
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
	*/
	Draw_Grid(21,10,0,underMap,window);
	Draw_Grid(21,11,1,map,window);
}

void Grid::DebugDraw(int nblines, int nbcols, block **grille)
{
	for (int ligne = 0; ligne < nblines; ligne++)
	{
		for (int colonne = 0; colonne < nbcols; colonne++)
			printf("%d ", grille[ligne][colonne]);
		printf("\n");
	}
}

void Grid::Draw_Grid(int nblines, int nbcols, int decalage, block **grille, sf::RenderWindow &window)
{
	sf::RectangleShape cell(sf::Vector2f(SIZECELL,SIZECELL));

	for (int ligne = 0; ligne < nblines; ligne++)
	{
		for (int colonne = decalage; colonne < nbcols; colonne++)
		{
			cell.setFillColor(color[grille[ligne][colonne]]);
			cell.setPosition((colonne - decalage) * SIZECELL, ligne * SIZECELL);
			window.draw(cell);
		}
	}
}
