#include <SFML/Graphics.hpp>
#include "headers/game.hpp"

int main()
{
    Game game;
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(300,600),"Tetris");

    game.run(window,event);

    return 0;
}