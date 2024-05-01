#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "headers/grid.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(300,600), "T�tris");
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
						tetromino.Move(true);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						tetromino.Move(false);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						tetromino.Rotate();

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						limit = 200;

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						for(int c; true;);
					break;

				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Down)
						limit = 500;
					break;
			}
		}
		// update section
		sf::Time time = clock.getElapsedTime();
		if (grid.HasnotReachedStg(tetromino) && time.asMilliseconds() > limit)
		{
			tetromino.Fall();
			time = clock.restart();
		}
		
		if (grid.HasnotReachedStg(tetromino)) // ajoute le tetromino � la carte courante
		{
			grid.Add_block_to_map(tetromino);
			grid.DebugDraw();
		}
		else
		{
			grid.fixe_block(tetromino);
			tetromino = Tetromino();
      		printf("[DEBGUG] -> le tetromino a été posé\n");
		}
		printf("pos.x = %d\npos.y = %d\n", tetromino.pos[0], tetromino.pos[1]);

		// Display section
		window.clear();
		tetromino.DebugDraw();
		grid.Draw(window);
		window.display();

		bool test = true;
		printf("%d\n", test);

		grid.Clear_residus(tetromino); // supprime les r�sidus de block
	}

	return 0;
}
