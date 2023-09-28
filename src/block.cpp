#include "headers/block.hpp"
#include "headers/vector2.hpp"

Block::Block() : pos(0,0)
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

    // attribution de la position de spawn en fonction de la taille du block
    pos.x = 5 - (bk_size + 1) / 2;
    pos.y = 0;
}

int Block::block_size()
{
    return bk_size;
}

eBlock Block::data(int pos, int height)
{
    return (eBlock) block[pos][height];
}

bool Block::haveReechGround()
{
    if (pos.y >= 20 - bk_size - 1)
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
            if (pos.x > 0)
                pos.x--;

        // Bouge a droite
        if (dir == ebkmdRight)
            if (pos.x < 10 - bk_size)
                pos.x++;
    }
    return pos.x;
}

int Block::slide()
{
    if (!haveReechGround())
        pos.y++;
    return pos.y;
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

void Block::mergeWithGrid(eBlock grid[10][20])
{
    if (haveReechGround())
    {
        for (int i = 0; i < bk_size; i++)
        {
            for (int j = 0; j < bk_size; j++)
            {
                if (block[j][i] != 0)
                {
                    Vector2i gPos(0, 0);
                    gPos.x = pos.x + j;
                    gPos.y = pos.y + i;
                    grid[gPos.x][gPos.y] = block[pos.x + j][pos.y + i];
                }
            }
        }
    }
}

void Block::draw(sf::RenderWindow &window)
{
    sf::RectangleShape blockShape(sf::Vector2f(CellSize - 1, CellSize - 1));

    for (int i = 0; i < bk_size; i++)
    {
        for (int j = 0; j < bk_size; j++)
        {
            // affichage du block
            // couleur
            int currentCellValue = block[j][i];
            blockShape.setFillColor(bkColor[currentCellValue]);

            if (block[j][i] != 0)
                currentCellValue = 1;
            else
                currentCellValue = 0;

            blockShape.setOutlineThickness(1);
            blockShape.setOutlineColor(outlineColor[currentCellValue]);

            // position
            blockShape.setPosition((pos.x + j) * CellSize, (pos.y + i) * CellSize);

            // affichage
            window.draw(blockShape);
        }
    }
}