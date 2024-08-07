#include "headers/game.hpp"

// Contrôle du jeu
void Game::Get_Next_Tetro()
{
    next_tetro = (block)((int)(rand()%7));
}

void Game::Attribute_score_and_level(Grid *grid)
{
    // attribution du score
    switch (grid->NbLineFull())
    {
        case 1:
            score += 20;
            break;

        case 2:
            score += 20;
            break;

        case 3:
            score += 50;
            break;

        case 4:
            score += 100;
            break;

        default:
            break;
    }

    // attribution du niveau et donc de la vitesse de jeu
    if (score_next_level <= score)
    {
        level += 1;
        limit -= 50;
        score_next_level += 200;
    }
}

void Game::update(sf::RenderWindow &window)
{
    mpos.x = sf::Mouse::getPosition(window).x;
    mpos.y = sf::Mouse::getPosition(window).y;
    if (title_screen)
        stop = false;
}

void Game::Save_High_Score()
{
    std::ifstream read_file("res/high_score.txt");
    bool new_score = false;
    if (read_file)
    {
        std::string ligne;
        if (std::getline(read_file, ligne))
        {
            if (std::stoi(ligne) < score)
                new_score = true;
        }
    }
    read_file.close();

    if (new_score)
    {
        std::ofstream write_file("res/high_score.txt");
        if (write_file)
            write_file << score;
        write_file.close();
    }
}

// Affichage du jeu
void Game::Game_Over(sf::RenderWindow &window, bool game_over)
{
    if (game_over && !title_screen)
    {
        stop = true;
        // dessiner le carrée noir
        sf::RectangleShape black_rect(sf::Vector2f(300.0f,120.0f));
        black_rect.setFillColor(sf::Color::Black);
        black_rect.setPosition(sf::Vector2f(0.0f,220.0f));

        // charger la font
        sf::Font font;
        font.loadFromFile("./res/font/Zorque.otf");

        // dessiner le texte de fin de jeu
        sf::Text text("Game Over", font, 30);
        text.setPosition(sf::Vector2f(60.0f, 260.0f));

        // afficher
        window.draw(black_rect);
        window.draw(text);
    }
}

void Game::DrawHUD(sf::RenderWindow &window, bool game_over)
{
    if (!title_screen)
    {
        Draw_Score(window);
        Draw_Next_Tetro(window);
        Draw_Score(window);
        Draw_High_Score(window);
        Draw_Level(window);
        Draw_Pause_Btn(window);
        if (game_over)
            DrawRetryBtn(window, game_over);
    }
}

void Game::DrawTitleScreen(sf::RenderWindow &window)
{
    if (title_screen)
    {
        // charger la font
        sf::Font font;
        font.loadFromFile("./res/font/Zorque.otf");

        // dessiner le texte de fin de jeu
        sf::Text T("T", font, 70);
        T.setPosition(sf::Vector2f(30.0f, 50.0f));
        T.setFillColor(sf::Color(255,0,0));
        sf::Text E("e", font, 70);
        E.setPosition(sf::Vector2f(70.0f, 50.0f));
        E.setFillColor(sf::Color(245, 89, 5));
        sf::Text t("t", font, 70);
        t.setPosition(sf::Vector2f(120.0f, 50.0f));
        t.setFillColor(sf::Color(255,255,0));
        sf::Text R("R", font, 70);
        R.setPosition(sf::Vector2f(160.0f, 50.0f));
        R.setFillColor(sf::Color(37, 250, 5));
        sf::Text I("I", font, 70);
        I.setPosition(sf::Vector2f(205.0f, 50.0f));
        I.setFillColor(sf::Color(5, 201, 245));
        sf::Text S("S", font, 70);
        S.setPosition(sf::Vector2f(230.0f, 50.0f));
        S.setFillColor(sf::Color::Magenta);


        sf::RectangleShape rect(sf::Vector2f(200.0f,75.0f));
        rect.setFillColor(sf::Color::White);
        rect.setPosition(sf::Vector2f(350.0f,475.0f));
        rect.setOutlineColor(sf::Color(143,143,143));
        rect.setOutlineThickness(4);

        // dessiner le texte
        sf::Text text_play("Play", font, 40);
        text_play.setPosition(sf::Vector2f(400.0f, 485.0f));
        text_play.setFillColor(sf::Color::Black);

        // afficher
        window.draw(rect);
        window.draw(text_play);
        window.draw(T);
        window.draw(E);
        window.draw(t);
        window.draw(R);
        window.draw(I);
        window.draw(S);
    }
}

void Game::DrawRetryBtn(sf::RenderWindow &window, bool game_over)
{
    sf::RectangleShape rect(sf::Vector2f(200.0f,75.0f));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(sf::Vector2f(350.0f,475.0f));
    rect.setOutlineColor(sf::Color(143,143,143));
    rect.setOutlineThickness(4);

    // charger la font
    sf::Font font;
    font.loadFromFile("./res/font/Zorque.otf");

    // dessiner le texte
    sf::Text text("Retry", font, 40);
    text.setPosition(sf::Vector2f(385.0f, 485.0f));
    text.setFillColor(sf::Color::Black);

    window.draw(rect);
    window.draw(text);
}

void Game::Pause(sf::RenderWindow &window, bool pause)
{
    if (pause && !title_screen)
    {
        // dessiner le carrée noir
        sf::RectangleShape black_rect(sf::Vector2f(300.0f,120.0f));
        black_rect.setFillColor(sf::Color::Black);
        black_rect.setPosition(sf::Vector2f(0.0f,220.0f));

        // charger la font
        sf::Font font;
        font.loadFromFile("./res/font/Zorque.otf");

        // dessiner le texte de fin de jeu
        sf::Text text("Pause", font, 33);
        text.setPosition(sf::Vector2f(90.0f, 260.0f));

        // afficher
        window.draw(black_rect);
        window.draw(text);
    }
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

void Game::Draw_Score(sf::RenderWindow &window)
{
    sf::Font score_font;
    score_font.loadFromFile("./res/font/LiberationSans-Regular.ttf");

    sf::Text txt_score("Score : "+(std::to_string)(score), score_font, 30);
    txt_score.setPosition(sf::Vector2f(350.0f, 275.0f));

    window.draw(txt_score);
}

void Game::Draw_High_Score(sf::RenderWindow &window)
{
    std::ifstream file("res/high_score.txt");
    if (file)
    {
        std::string ligne;
        if (std::getline(file, ligne))
        {
            sf::Font high_score_font;
            high_score_font.loadFromFile("./res/font/LiberationSans-Regular.ttf");

            sf::Text txt_high_score("High score : "+(ligne), high_score_font, 30);
            txt_high_score.setPosition(sf::Vector2f(350.0f, 310.0f));
            window.draw(txt_high_score);
        }
    }
    file.close();
}

void Game::Draw_Level(sf::RenderWindow &window)
{
    sf::Font level_font;
    level_font.loadFromFile("./res/font/LiberationSans-Regular.ttf");

    sf::Text txt_level("Level : "+(std::to_string)(level), level_font, 30);
    txt_level.setPosition(sf::Vector2f(350.0f, 345.0f));

    window.draw(txt_level);
}

void Game::Draw_Pause_Btn(sf::RenderWindow &window)
{
    sf::RectangleShape btn(sf::Vector2f(20.0f,20.0f));
    btn.setFillColor(sf::Color::Black);
    btn.setOutlineThickness(3);
    btn.setOutlineColor(sf::Color(143,143,143));
    btn.setPosition(sf::Vector2f(15.0f,15.0f));

    sf::RectangleShape line1(sf::Vector2f(4, 13));
    line1.setPosition(sf::Vector2f(19.0f,18.0f));

    sf::RectangleShape line2(sf::Vector2f(4, 13));
    line2.setPosition(sf::Vector2f(27.0f,18.0f));
    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0].position = sf::Vector2f(20.0f, 20.0f);
    triangle[1].position = sf::Vector2f(30.0f, 25.0f);
    triangle[2].position = sf::Vector2f(20.0f, 30.0f);

    window.draw(btn);
    if (!stop)
    {
        window.draw(line1);
        window.draw(line2);
    }
    else
        window.draw(triangle);
}
