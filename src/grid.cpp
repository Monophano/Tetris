#include "headers/grid.hpp"

Grid::Grid()
{
    for (int i = 0; i < LINE; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            grid1[i][j] = 0;
            grid2[i][j] = 0;
        }
    }
}

void Grid::draw(sf::RenderWindow &window)
{
    sf::RectangleShape cellule(sf::Vector2f(SIZECELLULE,SIZECELLULE));

    for (int i = 0; i < LINE; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            // Dessin de la premiere grid
            int cellValue = grid1[i][j];
            cellule.setFillColor(color[cellValue]);
            cellule.setPosition(SIZECELLULE * i + 1, SIZECELLULE * j + 1);

            window.draw(cellule);

            // Dessin de la deuxième grid
            cellValue = grid2[i][j];
            cellule.setFillColor(color[cellValue]);
            cellule.setPosition(SIZECELLULE * i + 1, SIZECELLULE * j + 1);

            window.draw(cellule);
        }
    }
}