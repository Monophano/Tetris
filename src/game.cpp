#include <ctime>
#include "headers/game.hpp"

// Contrôle du jeu
void Game::Get_Next_Tetro()
{
    srand(time(nullptr));
    next_tetro = (block)((int)(rand()%7));
}

// Affichage du jeu
void Game::Game_Over(sf::RenderWindow &window)
{
    // dessiner le carrée noir
    sf::RectangleShape black_rect(sf::Vector2f(300.0f,120.0f));
    black_rect.setFillColor(sf::Color::Black);
    black_rect.setPosition(sf::Vector2f(0.0f,220.0f));

    // charger la font
    sf::Font font;
    font.loadFromFile("./res/font/Zorque.otf");

    // dessiner le texte de fin de jeu
    sf::Text text("Game Over", font, 30);
    text.setPosition(sf::Vector2f(54.0f, 260.0f));

    // afficher
    window.draw(black_rect);
    window.draw(text);
}

void Game::DrawBarreLateral(sf::RenderWindow &window)
{
    /*
    sf::RectangleShape background(sf::Vector2f(300,600));
    //background.setFillColor(sf::Color(3, 1, 66));
    background.setFillColor(sf::Color::Black);
    background.setPosition(sf::Vector2f(300,0));
    window.draw(background);
    */
    Draw_Score(window);
    Draw_Next_Tetro(window);
}

void Game::Draw_Score(sf::RenderWindow &window)
{
    sf::Font score_font;
    score_font.loadFromFile("./res/font/LiberationSans-Regular.ttf");

    sf::Text txt_score("Score : "+(std::to_string)(score), score_font, 30);
    txt_score.setPosition(sf::Vector2f(375.0f, 275.0f));

    window.draw(txt_score);
}

void Game::Draw_Next_Tetro(sf::RenderWindow &window)
{
    sf::RectangleShape rect(sf::Vector2f(150.0f,150.0f));
    rect.setFillColor(sf::Color::Transparent);
    rect.setPosition(sf::Vector2f(375.0f,75.0f));
    rect.setOutlineThickness(4);

    sf::Texture texture;
    texture.loadFromFile(path_img_tetro[next_tetro]);

    sf::Sprite sprite(texture);

    if (next_tetro != I && next_tetro != O)
        sprite.setPosition(sf::Vector2f(375.0f,75.0f));
    else if (next_tetro == I)
        sprite.setPosition(sf::Vector2f(425.0f,75.0f));
    else
        sprite.setPosition(sf::Vector2f(400.0f,100.0f));

    window.draw(rect);
    window.draw(sprite);
}
