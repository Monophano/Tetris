#pragma once

#include <SFML/Graphics.hpp>
#include "grid.hpp"

class Game
{
    public:
        void run(sf::RenderWindow &window, sf::Event &event);
    
    private:
        Grid grid;
        void pollEvent(sf::RenderWindow &window, sf::Event &event);
        void handleInput(sf::RenderWindow &window);
        void display(sf::RenderWindow &window);
};