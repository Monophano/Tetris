#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "headers/grid.hpp"

#define touche_gauche true
#define touche_droite false

//int inutile = 0;

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
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						window.close();

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						if (grid.HasnotCollidedWithStg(tetromino,touche_droite))
							tetromino.Move(true);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						if (grid.HasnotCollidedWithStg(tetromino,touche_gauche))
							tetromino.Move(false);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						if (grid.CanRotate(tetromino))
							tetromino.Rotate();

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						limit = 100;

					//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					//	inutile = 0;
					break;

				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Down)
						limit = 600;
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
		{
			grid.Add_block_to_map(tetromino);
			//grid.DebugDraw();
		}
		else
		{
			grid.fixe_block(tetromino);
			tetromino = Tetromino();
      		//printf("[DEBGUG] -> le tetromino a été posé\n");
		}
		//printf("pos.x = %d pos.y = %d\n", tetromino.pos[0], tetromino.pos[1]);

		// Display section
		window.clear();
		//tetromino.DebugDraw();
		grid.Draw(window);
		window.display();

		grid.Clear_residus(tetromino); // supprime les r�sidus de block
	}

	return 0;
}

/*
#include <utility>
#include <stdio.h>

int main()
{
	int tab[3][2];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			tab[i][j] = 0;

	for (int i = 0; i < 2; i++)
		tab[2][i] = 1;

	tab[1][0] = 9;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
			printf("%d ", tab[i][j]);
		printf("\n");
	}
	printf("\n");

	int index = 2;
	while (index > 0)
	{
		for (int i = 0; i < 2; i++)
			std::swap(tab[index-1][i], tab[index][i]);
		index--;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
			printf("%d ", tab[i][j]);
		printf("\n");
	}
	return 0;
}
*/