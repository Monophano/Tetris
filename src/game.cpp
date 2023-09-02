#include "headers/game.hpp"

Game::Game()
{
    
}

void Game::run(sf::RenderWindow &window, sf::Event &event)
{
    while (window.isOpen())
    {
        if (block == nullptr)
            block = new Block();

        timer.start();

        if (!drop)
        {
            if (timer.verifCount() > fallSpeed)
            {
                block->slide();
                timer.clear();
            }
        }
        else
        {
            if (timer.verifCount() > fallSpeed - dropFallSpeed)
            {
                block->slide();
                timer.clear();
            }
        }

        if (block->haveReechGround())
            block = new Block;

        grid.updateGrid(*block);

        pollEvent(window,event);
        display(window);
    }
}

void Game::pollEvent(sf::RenderWindow &window, sf::Event &event)
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

                if (&block != nullptr)
                {
                    if (event.key.code == sf::Keyboard::Up)
                        block->rot();

                    if (event.key.code == sf::Keyboard::Down)
                        drop = true;

                    if (event.key.code == sf::Keyboard::Right)
                        block->move(ebkmdRight);

                    if (event.key.code == sf::Keyboard::Left)
                        block->move(ebkmdLeft);
                }
                break;

            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Down)
                    drop = false;
                break;
        }
    }
}

void Game::display(sf::RenderWindow &window)
{
    window.clear();
    grid.draw(window);
    window.display();
}
