#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "headers/grid.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(300,600), "Tétris");
	sf::Event event;

	window.setFramerateLimit(60);

	Grid grid;
	Tetromino tetromino;
	sf::Clock clock;

	while (window.isOpen())
	{
		// Event Section
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						window.close();

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						if (grid.isValideMove(tetromino))
							tetromino.Move(true);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						if (grid.isValideMove(tetromino))
							tetromino.Move(false);
					break;
			}
		}
		
		int limit = 500; // pour l'instant

		// Update section
		sf::Time time = clock.getElapsedTime();
		if (time.asMilliseconds() > limit)
		{
			tetromino.Fall();
			time = clock.restart();
		}
		grid.Add_block_to_map(tetromino);
		printf("pos.x = %d\npos.y = %d\n", tetromino.pos[0], tetromino.pos[1]);

		// Display section
		window.clear();
		grid.Draw(window);
		window.display();

		grid.Clear_residus(tetromino); // supprime les résidus de block
	}

	return 0;
}