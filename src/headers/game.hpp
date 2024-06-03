#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "globals.hpp"

class Game
{
    public:
        // contrôle du jeu
        void Get_Next_Tetro();
        block next_tetro;
        int score = 0;

        // Affichage du jeu
        void Game_Over(sf::RenderWindow &window);
        void DrawBarreLateral(sf::RenderWindow &window);

    private:
        void Draw_Score(sf::RenderWindow &window);
        void Draw_Next_Tetro(sf::RenderWindow &window);
        std::vector<std::string> path_img_tetro {
            "res/img/I_preview.png",
            "res/img/O_preview.png",
            "res/img/T_preview.png",
            "res/img/L_preview.png",
            "res/img/J_preview.png",
            "res/img/Z_preview.png",
            "res/img/S_preview.png"
        };
};
