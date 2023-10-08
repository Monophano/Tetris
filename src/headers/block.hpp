#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include "vector2.hpp"

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
        const int CellSize = 30;

        std::vector<sf::Color> bkColor = {
            sf::Color::Transparent, // empty color
            sf::Color(0,255,255), // I color
            sf::Color(255,251,0), // O color
            sf::Color(189,0,255), // T color
            sf::Color(255,162,0), // L color2
            sf::Color(0,12,255),  // J color
            sf::Color(255,0,0),   // Z color
            sf::Color(42,255,0)   // S color
        };

        sf::Color outlineColor[2] = {
            sf::Color::Transparent,
            sf::Color::Black
        };

    public:
        Block();
        Vector2i pos;
        int block_size();
        int move(eBlockMDir dir);
        int slide();
        void rot();
        bool haveReechGround();
        eBlock data(int pos, int height);
        int block[4][4];
        void draw(sf::RenderWindow &window);
};
