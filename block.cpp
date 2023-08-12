#include "headers/block.hpp"
Block::Block(eBloc TypeBlock)
{
    switch (TypeBlock)
    {
        case bkVide: break;
        case bkI :  block_size = 4;
                    for (int i = 0; i < block_size; i++)
                    for (int j = 0; j < block_size; j++)                
                        block[i][j] = blockI[i][j];
                    break;
        case bkO :  block_size = 2;
                    for (int i = 0; i < block_size; i++)
                    for (int j = 0; j < block_size; j++)                
                        block[i][j] = blockO[i][j];
                    break;
        case bkT :  block_size = 3;
                    for (int i = 0; i < block_size; i++)
                    for (int j = 0; j < block_size; j++)                
                        block[i][j] = blockT[i][j];
                    break;
        case bkL :  block_size = 3;
                    for (int i = 0; i < block_size; i++)
                    for (int j = 0; j < block_size; j++)                
                        block[i][j] = blockL[i][j];
                    break;
        case bkJ :  block_size = 3;
                    for (int i = 0; i < block_size; i++)
                    for (int j = 0; j < block_size; j++)                
                        block[i][j] = blockJ[i][j];
                    break;
        case bkZ :  block_size = 3;
                    for (int i = 0; i < block_size; i++)
                    for (int j = 0; j < block_size; j++)                
                        block[i][j] = blockZ[i][j];
                    break;
        case bkS :  block_size = 3;
                    for (int i = 0; i < block_size; i++)
                    for (int j = 0; j < block_size; j++)                
                        block[i][j] = blockS[i][j];
                    break;
    }

}
