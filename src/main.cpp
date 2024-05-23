#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "headers/grid.hpp"

#define touche_gauche true
#define touche_droite false

int main()
{
	sf::RenderWindow window(sf::VideoMode(300,600), "Tetris");
	sf::Event event;

	window.setFramerateLimit(60);

	Grid grid;
	Tetromino tetromino;
	sf::Clock clock;

	int limit = 600; // pour l'instant

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
					switch (event.key.code)
					{
						case sf::Keyboard::Escape:
							window.close();
							break;

						case sf::Keyboard::Right:
							if (grid.HasnotCollidedWithStg(tetromino,touche_droite))
								tetromino.Move(true);
							break;

						case sf::Keyboard::Left:
							if (grid.HasnotCollidedWithStg(tetromino,touche_gauche))
								tetromino.Move(false);
							break;

						case sf::Keyboard::Up:
							if (grid.CanRotate(tetromino))
								tetromino.Rotate();
							break;

						case sf::Keyboard::Down:
							limit = 100;
							break;

						default:
							break;
					}
					break;

				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
						case sf::Keyboard::Down:
							limit = 600;
							break;

						default:
							break;
					}
					break;

				default:
					break;
			}
		}
		// update section
		grid.destroyLineFull();
		sf::Time time = clock.getElapsedTime();
		if (grid.HasnotReachedStg(tetromino) && time.asMilliseconds() > limit)
		{
			tetromino.Fall();
			time = clock.restart();
		}

		if (grid.HasnotReachedStg(tetromino)) // ajoute le tetromino � la carte courante
			grid.Add_block_to_map(tetromino);
		else
		{
			sf::Time timer_fixe = clock.getElapsedTime();
			if (timer_fixe.asMilliseconds() >= 500)
			{
				grid.Add_block_to_undermap(tetromino);
				tetromino = Tetromino();
			}
			else
				grid.Add_block_to_map(tetromino);
		}

		// Display section
		window.clear();
		//tetromino.DebugDraw();
		grid.Draw(window);
		window.display();

		grid.Clear_residus(tetromino); // supprime les r�sidus de block
	}

	return 0;
}
