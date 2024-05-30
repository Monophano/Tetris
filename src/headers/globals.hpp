#pragma once

const int ROW = 20;
const int COL = 10;

enum block
{
	I = 0,
	O = 1,
	T = 2,
	L = 3,
	J = 4,
	Z = 5,
	S = 6,
	vide = 7,
	nothing = 8
};

struct position {
	int x;
	int y;
};
