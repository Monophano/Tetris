#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "headers/tetromino.hpp"
#include "headers/grid.hpp"

#define touche_gauche true
#define touche_droite false

int main()
{
	sf::RenderWindow window(sf::VideoMode(300,600), "Tetris");
	sf::Event event;

	window.setFramerateLimit(60);

	Tetromino tetromino;
	Grid grid;
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
							if (tetromino.HasnotCollidedWithStg(grid,touche_droite))
								tetromino.Move(true);
							break;

						case sf::Keyboard::Left:
							if (tetromino.HasnotCollidedWithStg(grid,touche_gauche))
								tetromino.Move(false);
							break;

						case sf::Keyboard::Up:
							if (tetromino.CanRotate(grid))
								tetromino.Rotate();
							break;

						case sf::Keyboard::Down:
							limit = 100;
							break;

						case sf::Keyboard::Space:
							limit = 0;
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

						case sf::Keyboard::Space:
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
		if (tetromino.HasnotReachedStg(grid) && time.asMilliseconds() > limit)
		{
			tetromino.Fall();
			time = clock.restart();
		}

		if (tetromino.HasnotReachedStg(grid)) // ajoute le tetromino sur la carte courante
			tetromino.Add_block_to_map(grid);
		else
		{
			sf::Time timer_fixe = clock.getElapsedTime();
			if (timer_fixe.asMilliseconds() >= 500)
			{
				tetromino.Add_block_to_undermap(grid);
				tetromino = Tetromino();
			}
			else
				tetromino.Add_block_to_map(grid);
		}

		// Display section
		window.clear();
		//tetromino.DebugDraw();
		grid.Draw(window);
		window.display();

		tetromino.Clear_residus(grid); // supprime les résidus de block
	}

	return 0;
}
