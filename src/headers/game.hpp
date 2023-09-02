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
};