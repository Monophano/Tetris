#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Grid
{
    public:
        Grid();
        void draw(sf::RenderWindow &window);

    private:
        // Constante
        const float SIZECELLULE = 30.0f;
        const int LINE = 20 ; const int COLUMN = 10 ;

        // Grid
        int grid1[20][10]; // Grid du fond
        int grid2[20][10]; // Grid avant

        std::vector<sf::Color> color = {
            sf::Color(33, 34, 64), // 0
            sf::Color(3,209,255), // I
            sf::Color(192,3,255), // T
            sf::Color(3,255,7), // S
            sf::Color(255,3,40), // Z
            sf::Color(255,125,3), // L
            sf::Color(15,3,255), // J
            sf::Color::Yellow // O
        };
};