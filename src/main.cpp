#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "headers/tetromino.hpp"
#include "headers/grid.hpp"
#include "headers/game.hpp"

#define touche_gauche true
#define touche_droite false

int main()
{
	sf::RenderWindow window(sf::VideoMode(600,600), "Tetris");
	sf::Event event;

	window.setFramerateLimit(60);

	// Initialisation du premier tetromino
	Game game;
	game.Get_Next_Tetro(); // premier tetro du jeu
	Tetromino tetromino(game.next_tetro);
	game.Get_Next_Tetro(); // prochain tetro à arriver

	Grid grid;
	sf::Clock clock;

	// initialisation du jeu
	tetromino.Add_block_to_map(grid);
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
					// fermeture rapide du jeu
					if (event.key.code == sf::Keyboard::Escape)
						window.close();

					// Contrôle du jeu pendant la partis
					if (!tetromino.SpawnInAnOtherTetro(grid))
						switch (event.key.code)
						{
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
								limit = 50;
								break;

							case sf::Keyboard::Space:
								tetromino.HardDrop(grid); // descend tout en bas jusqu'à collisionner
								tetromino = Tetromino(game.next_tetro);
								game.Get_Next_Tetro();
								break;

							default:
								break;
						}
					break;

				case sf::Event::KeyReleased:
					// contrôle du jeu pendant la parti
					if (!tetromino.SpawnInAnOtherTetro(grid))
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
		if (!tetromino.SpawnInAnOtherTetro(grid)) // vérifie si le jeu est en état de game over
		{
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
					tetromino = Tetromino(game.next_tetro);
					game.Get_Next_Tetro();
				}
				else
					tetromino.Add_block_to_map(grid);
			}
		}

		// Display section
		window.clear();
		grid.Draw(window);
		game.DrawBarreLateral(window);

		if (tetromino.SpawnInAnOtherTetro(grid))
			game.Game_Over(window);
		window.display();

		if (!tetromino.SpawnInAnOtherTetro(grid))
			tetromino.Clear_residus(grid); // supprime les résidus de block
	}

	return 0;
}
