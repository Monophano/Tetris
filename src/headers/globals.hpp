#pragma once

const int ROW = 20;
const int COL = 10;

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

struct position {
	int x;
	int y;
};
