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

	int limit = 500; // pour l'instant

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

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						if (grid.isValideMove(tetromino))
							tetromino.Rotate();

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						if (grid.isValideMove(tetromino))
							limit = 200;
					break;

				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Down)
						limit = 500;
					break;
			}
		}

		// Update section
		sf::Time time = clock.getElapsedTime();
		if (grid.isValideMove(tetromino) && time.asMilliseconds() > limit)
		{
			tetromino.Fall();
			time = clock.restart();
		}

		if (grid.isValideMove(tetromino)) // ajoute le tetromino à la carte courante
		{
			grid.Add_block_to_map(tetromino);
		}
		else
		{
			grid.fixe_block(tetromino);
			tetromino = Tetromino();
		}
		printf("pos.x = %d\npos.y = %d\n", tetromino.pos[0], tetromino.pos[1]);
		printf("is valide move : %d\n", grid.isValideMove(tetromino));

		// Display section
		window.clear();
		tetromino.DebugDraw();
		grid.Draw(window);
		window.display();

		grid.Clear_residus(tetromino); // supprime les résidus de block
	}

	return 0;
}