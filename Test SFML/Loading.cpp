#include"Game.h"
void Game::Loading()
{
    sf::Text Title("Loading...", font, 170);
    sf::Vector2u screen = window.getSize();

    Title.setOrigin(Title.getGlobalBounds().width / 2, Title.getGlobalBounds().height / 2);
    Title.setPosition(screen.x / 2, screen.y / 2 - 100);
    Title.setFillColor(sf::Color::White);

    Texts.push_back(Title);
}