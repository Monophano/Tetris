#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/grid.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(330,660), "Tetris");
    sf::Event event;
    Grid grid;

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
            }
        }

        window.clear();
        grid.draw(window);
        window.display();
    }

    return 0;
}