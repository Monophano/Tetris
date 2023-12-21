#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(300,600), "Tetris");
	sf::Event event;

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
					switch (event.key.code)
					{
						case sf::Keyboard::Escape:
							window.close();
							break;
					}
					break;
			}

			window.clear();
			window.display();
		}
	}

	return 0;
}