#pragma once
#include <ctime>
#include <stdlib.h>
#include <stdio.h>

enum block
{
	I = 1,
	O = 2,
	T = 3,
	L = 4,
	J = 5,
	Z = 6,
	S = 7,
	vide = 0,
	nothing = 8
};

class Tetromino
{
	public:
		int bsize;
		void Move(bool droite);
		void Fall();
		block actual_block[4][4];
		int pos[2]; // 0 = x, 1 = y
		Tetromino();

	private:
		block BlockI[4][4] = {
			{vide,I,vide,vide},
			{vide,I,vide,vide},
			{vide,I,vide,vide},
			{vide,I,vide,vide}
		};

		block BlockO[2][2] = {
			{O,O},
			{O,O}
		};

		block BlockT[3][3] = {
			{T,T,T},
			{vide,T,vide},
			{vide,vide,vide}
		};

		block BlockL[3][3] = {
			{L,L,L},
			{L,vide,vide},
			{vide,vide,vide}
		};

		block BlockJ[3][3] = {
			{J,J,J},
			{vide,vide,J},
			{vide,vide,vide}
		};

		block BlockZ[3][3] = {
			{Z,Z,vide},
			{vide,Z,Z},
			{vide,vide,vide}
		};

		block BlockS[3][3] = {
			{vide,S,S},
			{S,S,vide},
			{vide,vide,vide}
		};
};