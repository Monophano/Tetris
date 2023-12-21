#include "headers/grid.hpp"

Grid::Grid()
{
	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			grid1[i][j] = 0;
		}
	}
}