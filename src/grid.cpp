#include "headers/grid.hpp"

Grid::Grid()
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			map[i][j] = vide;
}


void Grid::Add_block_to_map(Tetromino& tetromino)
{
	for (int ligne = 0; ligne < tetromino.bsize; ligne++)
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
			map[ligne + tetromino.pos[1]][colonne + tetromino.pos[0]] = tetromino.actual_block[ligne][colonne];
}

void Grid::Clear_residus(Tetromino& tetromino)
{
	for (int ligne = 0; ligne < tetromino.bsize; ligne++)
		for (int colonne = 0; colonne < tetromino.bsize; colonne++)
			map[ligne + tetromino.pos[1]][colonne + tetromino.pos[0]] = vide;
}

bool Grid::isValideMove(Tetromino &tetromino)
{
	for (int ligne = 0; ligne < ROW; ligne++)
	{
		for (int colonne = 0; colonne < COL; colonne++)
		{
			printf("coucou les amis");
		}
	}
	return true;
}

void Grid::Draw(sf::RenderWindow &window)
{
	sf::RectangleShape cell(sf::Vector2f(SIZECELL, SIZECELL));
	for (int ligne = 0; ligne < ROW; ligne++)
	{
		for (int colonne = 0; colonne < COL; colonne++)
		{
			cell.setFillColor(color[map[ligne][colonne]]);
			cell.setPosition(colonne * SIZECELL, ligne * SIZECELL);
			window.draw(cell);
			printf("%d ", map[ligne][colonne]);
		}
		printf("\n");
	}
	printf("\n");
}