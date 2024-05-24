#include "headers/game.hpp"

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
