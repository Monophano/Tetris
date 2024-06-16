#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
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
	Game *game = nullptr;
	grid = new Grid();
	game = new Game();
	sf::Clock clock;
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
					// mode pause
					if (!tetromino.SpawnInAnOtherTetro(grid) && !game->title_screen)
						if (event.key.code == sf::Keyboard::Escape)
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

					// Contrôle du jeu pendant la partis
					if (!game->stop && !game->title_screen)
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
								// Bouton pause
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

							/*
							if (tetromino.SpawnInAnOtherTetro(grid))
								// Bouton menu
								if ((game->mpos.x >= 350 && game->mpos.x < 550) && (game->mpos.y >= 475 && game->mpos.y <= 550))
								{
									game->Save_High_Score();
									delete grid;
									delete game;
									grid = new Grid();
									game = new Game();
								}
							*/

							if (tetromino.SpawnInAnOtherTetro(grid))
								// Bouton rejouer
								if ((game->mpos.x >= 350 && game->mpos.x < 550) && (game->mpos.y >= 475 && game->mpos.y <= 550))
								{
									game->Save_High_Score();
									delete grid;
									grid = new Grid();
									tetromino = Tetromino(game->next_tetro);
									game->Get_Next_Tetro();
									game->title_screen = false;
									game->score = 0;
									game->limit = 600;
									game->limit_tempon = game->limit;
									game->level = 1;
									game->stop = false;
								}

							if (game->title_screen)
								// bouton jouer
								if ((game->mpos.x >= 350 && game->mpos.x < 550) && (game->mpos.y >= 475 && game->mpos.y <= 550))
								{
									delete grid;
									grid = new Grid();
									tetromino = Tetromino(game->next_tetro);
									game->Get_Next_Tetro();
									game->title_screen = false;
									game->score = 0;
									game->limit = 600;
									game->limit_tempon = game->limit;
									game->level = 1;
								}
							break;

						default:
							break;
					}
					break;

				case sf::Event::KeyReleased:
					// contrôle du jeu pendant la parti
					if (!game->stop && !game->title_screen)
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
		bool game_over = tetromino.SpawnInAnOtherTetro(grid);

		// Display section
		window.clear();

		grid->Draw(window); // affichage de la grille de jeu

		// Affichage des menus / HUD
		game->DrawHUD(window, game_over);
		game->DrawTitleScreen(window);

		// affichage de l'état du jeu
		game->Game_Over(window, game_over);
		game->Pause(window, (!tetromino.SpawnInAnOtherTetro(grid) && game->stop));

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
