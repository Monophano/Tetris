#pragma once

#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "block.hpp"
#include "timer.hpp"

class Game
{
    public:
        Game();
        void run(sf::RenderWindow &window, sf::Event &event);
    
    private:
        Grid grid;
        Timer timer;
        Block *block = nullptr;
        int fallSpeed = 35;
        int dropFallSpeed = 20;
        bool drop = false;
        bool gameOver = false;
        void pollEvent(sf::RenderWindow &window, sf::Event &event);
        void display(sf::RenderWindow &window);
        std::vector<sf::Color> bkColor = {
            sf::Color::Transparent, // empty color
            sf::Color(0,255,255), // I color
            sf::Color(255,251,0), // O color
            sf::Color(189,0,255), // T color
            sf::Color(255,162,0), // L color
            sf::Color(0,12,255),  // J color
            sf::Color(255,0,0),   // Z color
            sf::Color(42,255,0)   // S color
        };
};