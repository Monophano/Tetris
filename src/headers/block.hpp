#pragma once
enum eBloc {
    bkVide = 0,
    bkI = 1,
    bkO = 2,
    bkT = 3,
    bkL = 4,
    bkJ = 5,
    bkZ = 6,
    bkS = 7
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
        int block[4][4];
        int block_size; 

        Block(eBloc TypeBlock);
        
};