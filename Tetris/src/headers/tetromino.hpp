#pragma once
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include "globals.hpp"

class Tetromino
{
	public:
		int bsize;
		void Move(bool droite);
		void Fall();
		void Rotate();
		int nice_bsize();
		void DebugDraw();
		block actual_block[4][4];
		position pos;
		Tetromino();

	private:
		block BlockI[4][4] = {
			{nothing,I,nothing,nothing},
			{nothing,I,nothing,nothing},
			{nothing,I,nothing,nothing},
			{nothing,I,nothing,nothing}
		};

		block BlockO[2][2] = {
			{O,O},
			{O,O}
		};

		block BlockT[3][3] = {
			{T,T,T},
			{nothing,T,nothing},
			{nothing,nothing,nothing}
		};

		block BlockL[3][3] = {
			{L,L,L},
			{L,nothing,nothing},
			{nothing,nothing,nothing}
		};

		block BlockJ[3][3] = {
			{J,J,J},
			{nothing,nothing,J},
			{nothing,nothing,nothing}
		};

		block BlockZ[3][3] = {
			{Z,Z,nothing},
			{nothing,Z,Z},
			{nothing,nothing,nothing}
		};

		block BlockS[3][3] = {
			{nothing,S,S},
			{S,S,nothing},
			{nothing,nothing,nothing}
		};
};