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
	
	for (int ligne = 0; ligne < ROW; ligne++)
	{
		map[ligne][0] = I;
		map[ligne][11] = I;
	}

	/*
	for (int ligne = 0; ligne < 21; ligne++)
	{
		for (int colonne = 0; colonne < COL; colonne++)
		{
			printf("%d ", map[ligne][colonne]);
		}
		printf("\n");
	}
	*/
}


void Grid::Add_block_to_map(Tetromino &tetromino)
{
	for (int ligne = 0; ligne < tetromino.bsize; ligne++)
	{
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
		{
			if (tetromino.actual_block[ligne][colonne] != nothing)
				map[ligne + tetromino.pos[1]][colonne + tetromino.pos[0]] = tetromino.actual_block[ligne][colonne];
		}
	}
}

void Grid::Clear_residus(Tetromino &tetromino)
{
	for (int ligne = 0; ligne < tetromino.bsize; ligne++)
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
			map[ligne + tetromino.pos[1]][colonne + tetromino.pos[0]] = nothing;
}


bool Grid::HasnotReachedStg(Tetromino &tetromino)
{
	for(int ligne = tetromino.bsize-1;  ligne >= 0 ; ligne--)
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
		{
			printf("\nligne = %d colonne = %d\n", ligne, colonne);
			if (tetromino.actual_block[ligne][colonne] != nothing)
				if (underMap[tetromino.pos[1] + ligne + 1][(tetromino.pos[0]-1) + colonne] != vide)
					return false;
		}
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
					if (underMap[tetromino.pos[1] + ligne][(tetromino.pos[0] + colonne) - 1] != vide)
						return false;

		// collision avec les bords de la carte
		for (int ligne = 0; ligne < tetromino.bsize; ligne++)
			for (int colonne = 0; colonne < tetromino.bsize; colonne++)
				if (tetromino.actual_block[ligne][colonne] != nothing)
					if (map[tetromino.pos[1] + ligne][(tetromino.pos[0] + colonne) - 1] != nothing)
						return false;
	}
	else
	{
		// collision avec les autres tetrominos sur les côtés
		for (int ligne = 0; ligne < tetromino.bsize; ligne++)
			for (int colonne = tetromino.bsize - 1; colonne >= 0; colonne--)
				if (tetromino.actual_block[ligne][colonne] != nothing)
					if (underMap[tetromino.pos[1] + ligne][(tetromino.pos[0] + colonne) + 1] != vide)
						return false;

		// collision avec les bords de la carte
		for (int ligne = 0; ligne < tetromino.bsize; ligne++)
			for (int colonne = tetromino.bsize - 1; colonne >= 0; colonne--)
				if (tetromino.actual_block[ligne][colonne] != nothing)
					if (map[tetromino.pos[1] + ligne][(tetromino.pos[0] + colonne) + 1] != nothing)
						return false;
	}
	return true;
}

void Grid::fixe_block(Tetromino &tetromino)
{
	int pos_temp[2] = { tetromino.pos[0], tetromino.pos[1] };
	for (int ligne = 0; ligne < tetromino.bsize; ligne++)
	{
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
		{
			if (tetromino.actual_block[ligne][colonne] != nothing)
				underMap[ligne + pos_temp[1]][colonne + (pos_temp[0]-1)] = tetromino.actual_block[ligne][colonne];
		}
	}
}

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
