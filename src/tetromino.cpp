#include "headers/tetromino.hpp"

Tetromino::Tetromino(block numblock)
{
	switch (numblock)
	{
		case I:
			bsize = 4;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockI[i][j];
			pos.x = 5;
			break;

		case O:
			bsize = 2;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockO[i][j];
			pos.x = 4;
			break;

		case T:
			bsize = 3;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockT[i][j];
			pos.x = 4;
			break;

		case L:
			bsize = 3;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockL[i][j];
			pos.x = 4;
			break;

		case J:
			bsize = 3;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockJ[i][j];
			pos.x = 4;
			break;

		case Z:
			bsize = 3;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockZ[i][j];
			pos.x = 4;
			break;

		case S:
			bsize = 3;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockS[i][j];
			pos.x = 4;
			break;

		default:
			break;
	}
	pos.y = 0;
}

// Mouvement
void Tetromino::Move(bool droite)
{
	if (droite)
		pos.x++;
	else // gauche
		pos.x--;
}

void Tetromino::Fall()
{
	pos.y++;
}

void Tetromino::HardDrop(Grid &grid)
{
	// descendre tant que le tetromino ne touche pas le sol
	bool continuer = true;
	while (continuer)
	{
		if (HasnotReachedStg(grid))
			pos.y++;
		else
		{
			Add_block_to_undermap(grid);
			continuer = false;
		}
	}
}

void Tetromino::Rotate()
{
	block temp[4][4];

	// Effectuer la rotation
	for (int i = 0; i < bsize; ++i) {
		for (int j = 0; j < bsize; ++j) {
			temp[i][j] = actual_block[bsize - j - 1][i];
		}
	}

	// copier la liste temp dans actual_block
	for (int i = 0; i < bsize; ++i) {
		for (int j = 0; j < bsize; ++j) {
			actual_block[i][j] = temp[i][j];
		}
	}
}

/* Ajout d'un tetromino � la grille de jeu */
void Tetromino::Add_block_to_map(Grid &grid)
{
	for (int ligne = 0; ligne < bsize; ligne++)
	{
		for (int colonne = 0; colonne < bsize; colonne++)
		{
			if (actual_block[ligne][colonne] != nothing)
				grid.map[ligne + pos.y][colonne + pos.x] = actual_block[ligne][colonne];
		}
	}
}

void Tetromino::Add_block_to_undermap(Grid &grid)
{
	position pos_temp;
	pos_temp.x = pos.x;
	pos_temp.y = pos.y;

	for (int ligne = 0; ligne <bsize; ligne++)
		for (int colonne = 0; colonne < bsize; colonne++)
			if (actual_block[ligne][colonne] != nothing)
				grid.underMap[ligne + pos_temp.y][colonne + (pos_temp.x - 1)] = actual_block[ligne][colonne];
}

void Tetromino::Clear_residus(Grid &grid)
{
	for (int ligne = 0; ligne < bsize; ligne++)
		for (int colonne = 0; colonne < bsize; colonne++)
			if (actual_block[ligne][colonne] != nothing)
				grid.map[ligne + pos.y][colonne + pos.x] = nothing;
}

/* Collision */
bool Tetromino::HasnotReachedStg(Grid &grid)
{
	for(int ligne = bsize-1;  ligne >= 0 ; ligne--)
		for (int colonne = 0; colonne < bsize; colonne++)
			if (actual_block[ligne][colonne] != nothing)
				if (grid.underMap[pos.y + ligne + 1][(pos.x - 1) + colonne] != vide)
					return false;
	return true;
}

bool Tetromino::HasnotCollidedWithStg(Grid &grid, bool touche_gauche)
{
	if (touche_gauche)
	{
		// collision avec les autres tetrominos sur les c�t�s
		for (int ligne = 0; ligne < bsize; ligne++)
			for (int colonne = 0; colonne < bsize; colonne++)
				if (actual_block[ligne][colonne] != nothing)
					if (grid.underMap[pos.y + ligne][((pos.x-1) + colonne) - 1] != vide)
						return false;

		// collision avec les bords de la carte
		for (int ligne = 0; ligne < bsize; ligne++)
			for (int colonne = 0; colonne < bsize; colonne++)
				if (actual_block[ligne][colonne] != nothing)
					if (grid.map[pos.y + ligne][(pos.x + colonne) - 1] != nothing)
						return false;
	}
	else
	{
		// collision avec les autres tetrominos sur les c�t�s
		for (int ligne = 0; ligne < bsize; ligne++)
			for (int colonne = bsize - 1; colonne >= 0; colonne--)
				if (actual_block[ligne][colonne] != nothing)
					if (grid.underMap[pos.y + ligne][((pos.x-1) + colonne) + 1] != vide)
						return false;

		// collision avec les bords de la carte
		for (int ligne = 0; ligne < bsize; ligne++)
			for (int colonne = bsize - 1; colonne >= 0; colonne--)
				if (actual_block[ligne][colonne] != nothing)
					if (grid.map[pos.y + ligne][(pos.x + colonne) + 1] != nothing)
						return false;
	}
	return true;
}

bool Tetromino::CanRotate(Grid &grid)
{
	// verifier si un bout du tetromino est sorti de la carte
	for (int ligne = 0; ligne < bsize; ligne++)
	{
		for (int colonne = 0; colonne < bsize; colonne++)
			if (colonne + pos.x <= 0 // check rotation in the left side
				|| colonne + pos.x > 10 // check rotation in the right side
				|| grid.underMap[ligne + pos.y][colonne + (pos.x-1)] != vide) // check rotation against another tetromino
				return false;
	}

	return true;
}

// Fin de jeu ?
bool Tetromino::SpawnInAnOtherTetro(Grid& grid)
{
	for (int ligne = 0; ligne < bsize; ligne++)
		for (int colonne = 0; colonne < bsize; colonne++)
			if (pos.y == 0)
				if (actual_block[ligne][colonne] != nothing)
					if (grid.underMap[ligne + pos.y][colonne + (pos.x - 1)] != vide)
						return true;

	return false;
}

// Debug
void Tetromino::DebugDraw()
{
	for (int ligne = 0; ligne < bsize; ligne++)
	{
		for (int colonne = 0; colonne < bsize; colonne++)
		{
			printf("%d ", actual_block[ligne][colonne]);
		}
		printf("\n");
	}
	printf("\n");
}
