#include "headers/game.hpp"

void Game::run(sf::RenderWindow &window, sf::Event &event)
{
    grid.init();
    while (window.isOpen())
    {
        pollEvent(window,event);
        handleInput(window);
        display(window);
    }
}

void Game::pollEvent(sf::RenderWindow &window, sf::Event &event)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::handleInput(sf::RenderWindow &window)
{
    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

void Game::display(sf::RenderWindow &window)
{
    window.clear();
    grid.draw(window);
    window.display();
}