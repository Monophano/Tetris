#include "headers/grid.hpp"

Grid::Grid()
{
	for (int ligne = 0; ligne < ROW; ligne++)
		for (int colonne = 0; colonne < COL; colonne++)
			map[ligne][colonne] = nothing;

	for (int ligne = 0; ligne < ROW; ligne++)
		for (int colonne = 0; colonne < COL; colonne++)
			underMap[ligne][colonne] = vide;

	for (int colonne = 0; colonne < COL; colonne++) // Initialise Laste Row with a complete line to simplify colision detection on last line
		underMap[20][colonne] = I;

  for (int ligne = 0; ligne < 21; ligne++) // Init first COL with a complete line to simplify colision detection on left side
    map[ligne][0] = I;

  for (int ligne = 0; ligne < 21; ligne++) // Init last COL with a complete line to simplify colision detection on right side
    map[ligne][11] = I;

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
	for(int l = tetromino.bsize-1;  l >= 0 ; l--)
		for(int c = 0;  c < tetromino.bsize; c++)
		{
			if (tetromino.actual_block[l][c] != nothing)
			{
				if ( underMap[tetromino.pos[1]+l+1][tetromino.pos[0]+c] != vide)
				{
					printf("Move non valide\n");
					return false;
				}
			}
		}
	printf("Move valide\n");
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
				underMap[ligne + pos_temp[1]][colonne + pos_temp[0]] = tetromino.actual_block[ligne][colonne];
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
		for (int colonne = 1; colonne < COL; colonne++)
		{
			cell.setFillColor(color[map[ligne][colonne]]);
			cell.setPosition(colonne * SIZECELL, ligne * SIZECELL);
			window.draw(cell);
		}
	}
}

void Grid::DebugDraw()
{
	printf("Map :                 	UnderMap :\n");
	for (int ligne = 0; ligne < REALROW; ligne++)
	{
		// Map
		for (int colonne = 0; colonne < MAPCOL; colonne ++)
			printf("%d ", map[ligne][colonne]);

		printf("	");

		// UnderMap
		for (int colonne = 0; colonne < COL; colonne ++)
			printf("%d ", underMap[ligne][colonne]);

		printf("\n");
	}
}
