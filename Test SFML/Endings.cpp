#include"Game.h"
void Game::Ending(int mode)
{
    sf::Text Title("", font, 170);
    sf::Vector2u screen = window.getSize();
    sf::Text Continue("CONTINUE?", font, 80);
    sf::Text Yes("YES", font, 50);
    sf::Text No("NO", font, 50);
    if (mode == 1) {
        Title.setString("YO WIN!!");
    }
    else if (mode == 0) {
        Title.setString("YOU LOSE!!");
    }
    Title.setOrigin(Title.getGlobalBounds().width / 2, Title.getGlobalBounds().height / 2);
    Title.setPosition(screen.x / 2, Title.getGlobalBounds().height / 2 + 100);
    Title.setFillColor(sf::Color::White);

    Continue.setOrigin(Continue.getGlobalBounds().width / 2, Continue.getGlobalBounds().height / 2);
    Continue.setPosition(screen.x / 2, Title.getPosition().y + 200);
    Continue.setFillColor(sf::Color::White);

    Yes.setOrigin(Yes.getGlobalBounds().width / 2, Yes.getGlobalBounds().height / 2);
    Yes.setPosition(screen.x / 2 - 150, Continue.getPosition().y + 150);
    Yes.setFillColor(sf::Color::White);

    No.setOrigin(No.getGlobalBounds().width / 2, No.getGlobalBounds().height / 2);
    No.setPosition(screen.x / 2 + 150, Continue.getPosition().y + 150);
    No.setFillColor(sf::Color::White);
    Texts.push_back(Title);
    Texts.push_back(Continue);
    Buttons.push_back(Yes);
    Buttons.push_back(No);
}