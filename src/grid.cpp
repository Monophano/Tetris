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

	for (int ligne = 0; ligne < 21; ligne++)
	{
		for (int colonne = 0; colonne < COL; colonne++)
		{
			printf("%d ", map[ligne][colonne]);
		}
		printf("\n");
	}
}

/* Ajout d'un tetromino à la grille de jeu */
void Grid::Add_block_to_map(Tetromino &tetromino)
{
	for (int ligne = 0; ligne < tetromino.bsize; ligne++)
	{
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
		{
			if (tetromino.actual_block[ligne][colonne] != nothing)
				map[ligne + tetromino.pos.y][colonne + tetromino.pos.x] = tetromino.actual_block[ligne][colonne];
		}
	}
}

void Grid::fixe_block(Tetromino& tetromino)
{
	position pos_temp;
	pos_temp.x = tetromino.pos.x;
	pos_temp.y = tetromino.pos.y;

	for (int ligne = 0; ligne < tetromino.bsize; ligne++)
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
			if (tetromino.actual_block[ligne][colonne] != nothing)
				underMap[ligne + pos_temp.y][colonne + (pos_temp.x - 1)] = tetromino.actual_block[ligne][colonne];
}

void Grid::Clear_residus(Tetromino &tetromino)
{
	for (int ligne = 0; ligne < tetromino.bsize; ligne++)
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
			if (tetromino.actual_block[ligne][colonne] != nothing)
				map[ligne + tetromino.pos.y][colonne + tetromino.pos.x] = nothing;
}

/* Collision */
bool Grid::HasnotReachedStg(Tetromino &tetromino)
{
	for(int ligne = tetromino.bsize-1;  ligne >= 0 ; ligne--)
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
			if (tetromino.actual_block[ligne][colonne] != nothing)
				if (underMap[tetromino.pos.y + ligne + 1][(tetromino.pos.x-1) + colonne] != vide)
					return false;
	return true;
}

bool Grid::HasnotCollidedWithStg(Tetromino &tetromino, bool touche_gauche)
{
	if (touche_gauche)
	{
		// collision avec les autres tetrominos sur les côtés
		for (int ligne = 0; ligne < tetromino.bsize; ligne++)
			for (int colonne = 0; colonne < tetromino.bsize; colonne++)
				if (tetromino.actual_block[ligne][colonne] != nothing)
					if (underMap[tetromino.pos.y + ligne][((tetromino.pos.x-1) + colonne) - 1] != vide)
						return false;

		// collision avec les bords de la carte
		for (int ligne = 0; ligne < tetromino.bsize; ligne++)
			for (int colonne = 0; colonne < tetromino.bsize; colonne++)
				if (tetromino.actual_block[ligne][colonne] != nothing)
					if (map[tetromino.pos.y + ligne][(tetromino.pos.x + colonne) - 1] != nothing)
						return false;
	}
	else
	{
		// collision avec les autres tetrominos sur les côtés
		for (int ligne = 0; ligne < tetromino.bsize; ligne++)
			for (int colonne = tetromino.bsize - 1; colonne >= 0; colonne--)
				if (tetromino.actual_block[ligne][colonne] != nothing)
					if (underMap[tetromino.pos.y + ligne][((tetromino.pos.x-1) + colonne) + 1] != vide)
						return false;

		// collision avec les bords de la carte
		for (int ligne = 0; ligne < tetromino.bsize; ligne++)
			for (int colonne = tetromino.bsize - 1; colonne >= 0; colonne--)
				if (tetromino.actual_block[ligne][colonne] != nothing)
					if (map[tetromino.pos.y + ligne][(tetromino.pos.x + colonne) + 1] != nothing)
						return false;
	}
	return true;
}

bool Grid::CanRotate(Tetromino& tetromino)
{
	// verifier si un bout du tetromino est sorti de la carte
	for (int ligne = 0; ligne < tetromino.bsize; ligne++)
	{
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
			if (colonne + tetromino.pos.x <= 0 // check rotation in the left side
				|| colonne + tetromino.pos.x > 10 // check rotation in the right side
				|| underMap[ligne + tetromino.pos.y][colonne + (tetromino.pos.x-1)] != vide // check rotation against another tetromino
				)
				return false;
	}

	return true;
}

/* gestion de la ligne complète */
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

				// puis on la déplace tout en haut en déplacant les lignes une après l'autre
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
