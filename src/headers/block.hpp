#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>

enum eBlock
{
    bkI = 1,
    bkO = 2,
    bkT = 3,
    bkL = 4,
    bkJ = 5,
    bkZ = 6,
    bkS = 7
};

enum eBlockMDir
{
    ebkmdLeft = false,
    ebkmdRight = true
};

class Block
{
    private:
        int blockI[4][4] = {
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0}
        };

        int blockO[2][2] = {
            {2,2},
            {2,2}
        };

        int blockT[3][3] = {
            {0,3,0},
            {3,3,3},
            {0,0,0}
        };

        int blockL[3][3] = {
            {4,4,0},
            {0,4,0},
            {0,4,0}
        };

        int blockJ[3][3] = {
            {0,5,5},
            {0,5,0},
            {0,5,0}
        };

        int blockZ[3][3] = {
            {0,6,0},
            {6,6,0},
            {6,0,0}
        };

        int blockS[3][3] = {
            {0,7,0},
            {0,7,7},
            {0,0,7}
        };

        int bk_size = 0;
        int block[4][4];
        int pos[2];

    public:
        Block();
        int block_size();
        int block_pos_x();
        int block_pos_y();
        int block_height();
        int block_width();
        int move(eBlockMDir dir);
        int slide();
        void rot();
        bool haveReechGround();
        eBlock data(int pos, int height);
};
