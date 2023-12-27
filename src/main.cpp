#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(300,600), "Tetris");
    sf::Event event;

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
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}