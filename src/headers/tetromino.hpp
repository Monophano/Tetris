#pragma once
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include "grid.hpp"

class Tetromino
{
	public:
		Tetromino(block numblock);

		// mouvement du tetromino
		void Move(bool droite);
		void Fall();
		void HardDrop(Grid &grid);
		void Rotate();

		// positionnement du tetromino dans la grille
		void Add_block_to_map(Grid &grid);
		void Add_block_to_undermap(Grid &grid);
		void Clear_residus(Grid &grid);

		// collision
		bool HasnotReachedStg(Grid &grid);
		bool HasnotCollidedWithStg(Grid &grid, bool touche_gauche);
		bool CanRotate(Grid &grid);

		// Fin de jeu ?
		bool SpawnInAnOtherTetro(Grid &grid);

		// Debug
		void DebugDraw();

	private:
		block actual_block[4][4];
		position pos;
		int bsize;

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
			{nothing,nothing,nothing},
			{nothing,T,nothing},
			{T,T,T}
		};

		block BlockL[3][3] = {
			{L,L,L},
			{L,nothing,nothing},
			{nothing,nothing,nothing}
		};

		block BlockJ[3][3] = {
			{J,nothing,nothing},
			{J,J,J},
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
