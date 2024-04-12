#include "headers/tetromino.hpp"

Tetromino::Tetromino()
{
	srand(time(nullptr));
	block numblock = (block)((int)(rand()%7+1));
	printf("Le block choisis est %d\n", numblock);
	switch (numblock)
	{
	case I:
		bsize = 4;
		for (int i = 0; i < bsize; i++)
			for (int j = 0; j < bsize; j++)
				actual_block[i][j] = BlockI[i][j];
			pos[0] = 5;
			break;

		case O:
			bsize = 2;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockO[i][j];
			pos[0] = 4;
			break;

		case T:
			bsize = 3;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockT[i][j];
			pos[0] = 4;
			break;

		case L:
			bsize = 3;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockL[i][j];
			pos[0] = 4;
			break;

		case J:
			bsize = 3;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockJ[i][j];
			pos[0] = 4;
			break;

		case Z:
			bsize = 3;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockZ[i][j];
			pos[0] = 4;
			break;

		case S:
			bsize = 3;
			for (int i = 0; i < bsize; i++)
				for (int j = 0; j < bsize; j++)
					actual_block[i][j] = BlockS[i][j];
			pos[0] = 4;
			break;
	}
	pos[1] = 0;
}

void Tetromino::Move(bool droite)
{
	if (droite)
		pos[0]++;
	else // gauche
		pos[0]--;
}

void Tetromino::Fall()
{
	pos[1]++;
}