#include "headers/tetromino.hpp"

Tetromino::Tetromino()
{
	srand(time(nullptr));
	block numblock = (block)((int)(rand()%7+1));
	//numblock = L;
	printf("Le block choisis est %d\n", numblock);
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
	}
	pos.y = 0;
}

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


int Tetromino::nice_bsize()
{
	// get right bsize
	int bsize_temp = 0;
	int nice_bsize = 0;
	for (int colonne = 0; colonne < bsize; colonne++)
  {
		for (int ligne = 0; ligne < bsize; ligne++)
		{
			if (actual_block[ligne][colonne] != nothing)
				bsize_temp++;
		}
		if (bsize_temp > nice_bsize)
		nice_bsize = bsize_temp;
		bsize_temp = 0;
  }	
	printf("\nnice_bsize = %d\n", nice_bsize);
	
	return nice_bsize;
}


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
