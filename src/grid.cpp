#include "headers/grid.hpp"

Grid::Grid()
{
    init();
}

void Grid::init()
{
    for (int line = 0; line < numLine; line++)
    for (int column = 0; column < numColumn; column++)
        grid[column][line] = bkVide;
}

void Grid::draw(sf::RenderWindow &window)
{
    sf::RectangleShape cellule(sf::Vector2f(cellSize - 1, cellSize - 1));
//    sf::RectangleShape cellule(sf::Vector2<float>(29, 29));

    // dessiner les cellules
    for (int line = 0; line < numLine; line++)
    {
        for (int column = 0; column < numColumn; column++)
        {
            // definition de la couleur des cellules
            int cellValue = grid[column][line];
            cellule.setFillColor(colors[cellValue]);

            // definition de la position
            cellule.setPosition(column * cellSize + 1,line * cellSize + 1);

            // affichage
            window.draw(cellule);
        }
    }
}

void Grid::updateGrid(Block block)
{
    for (int i = block.block_pos(); i < block.block_pos() + block.block_size(); i++)
        if (block.block_height() > 0)
            grid[i][block.block_height() - 1] = bkVide;

    for (int i = 0; i < block.block_size(); i++)
        for (int j = 0; j < block.block_size(); j++)
            grid[block.block_pos() + i][block.block_height() + j] = block.data(i, j);
}

void Grid::checkLineFull()
{
    // check if a line is full
    for (int i = 19; i > 0; i--)
    {
        bool Ligne_Full = true;
        for (int j = 0; j < 10 && !Ligne_Full; j++)
            Ligne_Full = grid[i][j] != bkVide;

        if (Ligne_Full)
            for (int k = i - 1; k > 0; k--)
                for (int j = 0; j < 10; j++)
                    grid[j][k + 1] = grid[j][k];
    }
}

void Grid::checkEnd()
{

}