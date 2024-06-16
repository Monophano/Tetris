#pragma once
#include "grid.hpp"
#include "globals.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>


class Game
{
    public:
        // contrôle du jeu
        void Get_Next_Tetro();
        void Attribute_score_and_level(Grid *grid);
        void Mouse_update(sf::RenderWindow &window);
        void Save_High_Score();
        bool title_screen = true;
        block next_tetro;
        int score = 0;
        int limit = 600; // par défaut
        int limit_tempon = limit;
        bool stop = false;
        int level = 1;
        Mouse_Position mpos;

        // Affichage du jeu
        void Game_Over(sf::RenderWindow &window, bool game_over);
        void DrawHUD(sf::RenderWindow &window, bool game_over);
        void DrawTitleScreen(sf::RenderWindow &window);
        void Pause(sf::RenderWindow &window, bool pause);

    private:
        int score_next_level = score + 200;
        void Draw_Pause_Btn(sf::RenderWindow &window);
        void DrawRetryBtn(sf::RenderWindow &window, bool game_over);
        void Draw_Next_Tetro(sf::RenderWindow &window);
        void Draw_Score(sf::RenderWindow &window);
        void Draw_High_Score(sf::RenderWindow &window);
        void Draw_Level(sf::RenderWindow &window);
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
