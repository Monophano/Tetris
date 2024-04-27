#include "headers/grid.hpp"

Grid::Grid()
{
	for (int ligne = 0; ligne < ROW; ligne++)
		for (int colonne = 0; colonne < COL; colonne++)
			map[ligne][colonne] = nothing;

	for (int ligne = 0; ligne < ROW; ligne++)
		for (int colonne = 0; colonne < COL; colonne++)
			underMap[ligne][colonne] = vide;
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

bool Grid::isValideMove(Tetromino &tetromino)
{
	// verify the move
	if (tetromino.pos[1] == 20 - tetromino.right_bsize())
		return false;
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
			//printf("%d ", underMap[ligne][colonne]);
		}
		//printf("\n");
	}
	//printf("\n");

	// Grille du dessus
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