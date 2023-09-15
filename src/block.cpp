#include "headers/block.hpp"

Block::Block()
{
    srand((unsigned int)time(0));
    eBlock TypeBlock = (eBlock)((((unsigned int)rand()) + 1) % 7);

    switch (TypeBlock)
    {
        case bkI :  bk_size = 4;
                    for (int i = 0; i < block_size(); i++)
                    for (int j = 0; j < block_size(); j++)                
                        block[i][j] = blockI[i][j];
                    break;

        case bkO :  bk_size = 2;
                    for (int i = 0; i < block_size(); i++)
                    for (int j = 0; j < block_size(); j++)                
                        block[i][j] = blockO[i][j];
                    break;

        case bkT :  bk_size = 3;
                    for (int i = 0; i < block_size(); i++)
                    for (int j = 0; j < block_size(); j++)                
                        block[i][j] = blockT[i][j];
                    break;

        case bkL :  bk_size = 3;
                    for (int i = 0; i < block_size(); i++)
                    for (int j = 0; j < block_size(); j++)                
                        block[i][j] = blockL[i][j];
                    break;

        case bkJ :  bk_size = 3;
                    for (int i = 0; i < block_size(); i++)
                    for (int j = 0; j < block_size(); j++)                
                        block[i][j] = blockJ[i][j];
                    break;

        case bkZ :  bk_size = 3;
                    for (int i = 0; i < block_size(); i++)
                    for (int j = 0; j < block_size(); j++)                
                        block[i][j] = blockZ[i][j];
                    break;

        case bkS :  bk_size = 3;
                    for (int i = 0; i < block_size(); i++)
                    for (int j = 0; j < block_size(); j++)                
                        block[i][j] = blockS[i][j];
                    break;
    }

    pos[0] = 0;
    pos[1] = 5 - (bk_size + 1) / 2;
}

int Block::block_size()
{
    return bk_size;
}

int Block::block_pos_x()
{
    return pos[1];
}

int Block::block_pos_y()
{
    return pos[1];
}

int Block::block_height()
{
    return pos[0];
}

int Block::block_width()
{
    return pos[1];
}

eBlock Block::data(int pos, int height)
{
    return (eBlock) block[pos][height];
}

bool Block::haveReechGround()
{
    if (pos[0] >= 20 - bk_size + 1)
    {
        return true;
    }
    return false;
}

int Block::move(eBlockMDir dir)
{
    if (!haveReechGround())
    {
        // Bouge a gauche
        if (dir == ebkmdLeft)
            if (pos[1] > 0)
                pos[1]--;

        // Bouge a droite
        if (dir == ebkmdRight)
            if (pos[1] < 10 - bk_size)
                pos[1]++;
    }
    return pos[1];
}

int Block::slide()
{
    if (!haveReechGround())
        pos[0]++;
    return pos[0];
}

void Block::rot()
{
    if (!haveReechGround())
    {
        int block_tmp[4][4];
        for (int i = 0; i < bk_size; i++)
            for (int j = 0; j < bk_size; j++)
                block_tmp[bk_size - j - 1][i] = block[i][j];

        for (int i = 0; i < bk_size; i++)
            for (int j = 0; j < bk_size; j++)
                block[i][j] = block_tmp[i][j];
    }
}
