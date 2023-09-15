#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "block.hpp"

class Grid
{
    public:
        Grid();
        void draw(sf::RenderWindow &window);
        void updateGrid(Block block);
        void checkLineFull();
        eBlock grid[10][20];

    private:
        bool lineFull = false;
        const int cellSize = 30;
        int numLine = 20;
        int numColumn = 10;
        int gridHeight = 20;
        int gridWidth = 10;
        std::vector<sf::Color> colors = {
            sf::Color(142,142,142), // empty color
            sf::Color(0,255,255), // I color
            sf::Color(255,251,0), // O color
            sf::Color(189,0,255), // T color
            sf::Color(255,162,0), // L color
            sf::Color(0,12,255),  // J color
            sf::Color(255,0,0),   // Z color
            sf::Color(42,255,0)   // S color
        };
        void init();
};