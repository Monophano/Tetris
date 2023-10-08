#include "headers/grid.hpp"

Grid::Grid()
{
    for (int line = 0; line < numLine; line++)
    for (int column = 0; column < numColumn; column++)
        grid[column][line] = (eBlock) 0;
}

void Grid::draw(sf::RenderWindow &window)
{
    sf::RectangleShape cellule(sf::Vector2f(cellSize - 1, cellSize - 1));

    // dessiner les cellules de la grille
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

int Grid::CellSize()
{
    return cellSize;
}

void Grid::updateGrid(Block block)
{
    // introduction des blocks dans la grille
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));

    for (int i = 0; i < block.block_size(); i++)
    {
        for (int j = 0; j < block.block_size(); j++)
        {

        }
    }
    
    // check line
    checkLineFull();
}

void Grid::checkLineFull()
{
    for (int i = 19; i > 0; i--)
    {
        for (int j = 0; j < 10 && !lineFull; j++)
            lineFull = grid[i][j] != 0;

        if (lineFull)
            for (int k = i - 1; k > 0; k--)
                for (int j = 0; j < 10; j++)
                    grid[j][k + 1] = grid[j][k];
    }
}
