#include "headers/grid.hpp"

void Grid::init()
{
    for (int line = 0; line < numLine; line++)
    {
        for (int column = 0; column < numColumn; column++)
        {
            grid[line][column] = 0;
            std::cout << grid[line][column] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::draw(sf::RenderWindow &window)
{
    sf::RectangleShape cellule(sf::Vector2f(cellSize - 1, cellSize - 1));

    // dessiner les cellules
    for (int line = 0; line < numLine; line++)
    {
        for (int column = 0; column < numColumn; column++)
        {
            // definition de la couleur des cellules
            int cellValue = grid[line][column];
            cellule.setFillColor(colors[cellValue]);

            // definition de la position
            cellule.setPosition(column * cellSize + 1,line * cellSize + 1);

            // affichage
            window.draw(cellule);
        }
    }
}