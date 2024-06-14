#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "headers/game.hpp"
#include "headers/tetromino.hpp"
#include "headers/grid.hpp"

#define touche_gauche true
#define touche_droite false

int main()
{
	sf::RenderWindow window(sf::VideoMode(600,600), "Tetris");
	sf::Event event;

	window.setFramerateLimit(60);

	// Initialisation du jeu
	Grid *grid = nullptr;
	grid = new Grid();
	sf::Clock clock;
	Game *game = nullptr;
	game = new Game();
	game->Get_Next_Tetro(); // premier tetro du jeu
	Tetromino tetromino(game->next_tetro);
	game->Get_Next_Tetro(); // prochain tetro à arriver

	// initialisation du jeu
	tetromino.Add_block_to_map(grid);
	bool touche_bas_presse = false;

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
					if (!tetromino.SpawnInAnOtherTetro(grid))
					{
						if (event.key.code == sf::Keyboard::Escape)
						{
							switch (game->stop)
							{
								case true:
									game->stop = false;
									tetromino.Clear_residus(grid);
									break;

								case false:
									game->stop = true;
									break;
							}
						}
					}

					// Contrôle du jeu pendant la partis
					if (!game->stop)
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
								if (touche_bas_presse == false)
									game->limit_tempon = game->limit;
								game->limit = 30;
								touche_bas_presse = true;
								break;

							case sf::Keyboard::Space:
								tetromino.HardDrop(grid); // descend tout en bas jusqu'à collisionner
								tetromino = Tetromino(game->next_tetro);
								game->Get_Next_Tetro();
								game->score += 10; // ajouter dix points quand un block est posé
								break;

							default:
								break;
						}
					break;

				case sf::Event::MouseButtonPressed:
					switch (event.mouseButton.button)
					{
						case sf::Mouse::Button::Left:
							if (!tetromino.SpawnInAnOtherTetro(grid))
								if ((game->mpos.x >= 15 && game->mpos.x <= 35) && (game->mpos.y >= 15 && game->mpos.y <= 35))
								{
									switch (game->stop)
									{
										case true:
											game->stop = false;
											tetromino.Clear_residus(grid);
											break;

										case false:
											game->stop = true;
											break;
									}
								}
							if (tetromino.SpawnInAnOtherTetro(grid))
								if ((game->mpos.x >= 350 && game->mpos.x < 550) && (game->mpos.y >= 475 && game->mpos.y <= 550))
								{
									delete grid;
									delete game;
									grid = new Grid();
									game = new Game();
								}
							break;

						default:
							break;
					}
					break;

				case sf::Event::KeyReleased:
					// contrôle du jeu pendant la parti
					if (!game->stop)
						switch (event.key.code)
						{
							case sf::Keyboard::Down:
								game->limit = game->limit_tempon;
								touche_bas_presse = false;
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
		if (!game->stop) // vérifie si le jeu est en état de game over
		{
			//printf("x: %d y: %d\n",game.mpos.x,game.mpos.y);
			game->Attribute_score_and_level(grid);
			grid->destroyLineFull();
			sf::Time time = clock.getElapsedTime();
			if (tetromino.HasnotReachedStg(grid) && time.asMilliseconds() > game->limit)
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
					tetromino = Tetromino(game->next_tetro);
					game->Get_Next_Tetro();
					game->score += 10; // ajouter dix points quand un block est posé
				}
				else
					tetromino.Add_block_to_map(grid);
			}
		}
		game->Mouse_update(window);

		// Display section
		window.clear();
		grid->Draw(window);
		game->DrawHUD(window);
		if (tetromino.SpawnInAnOtherTetro(grid))
		{
			game->stop = true;
			game->Game_Over(window);
			game->DrawRetryBtn(window);
		}
		if (!tetromino.SpawnInAnOtherTetro(grid) && game->stop)
			game->Pause(window);
		game->Draw_Pause_Btn(window);
		window.display();

		if (!game->stop) // supprime les résidus de block
			tetromino.Clear_residus(grid);
		else
		{
			tetromino.Clear_residus(grid);
			tetromino.Add_block_to_map(grid);
		}
	}

	return 0;
}
