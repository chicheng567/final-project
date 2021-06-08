#include "characters.h"
#include "Game.h"
void Game::gameStart()
{
    mainPlayer plyerOne("./textures/knight1/", sf::Vector2f(565 / 1.5, 368 / 1.5));
    shapes.push_back(plyerOne);  //create and push the character in the vector
    sf::RectangleShape  outback, background[4], range;
    sf::Texture* backgroundT = new sf::Texture[6];
    backgroundT[0].loadFromFile("./background/layers/background.png");
    backgroundT[1].loadFromFile("./background/layers/battleground.png");
    backgroundT[2].loadFromFile("./background/layers/back_land.png");
    backgroundT[3].loadFromFile("./background/layers/back_decor.png");
    backgroundT[4].loadFromFile("./background/layers/front_decor.png");
    backgroundT[5].loadFromFile("./background/layers/ground_decor.png");

    outback.setSize((sf::Vector2f)window.getSize());

    for (int i = 0; i < 4; i++) {
        background[i].setSize(sf::Vector2f(1920, window.getSize().y));
        background[i].setOrigin(background[i].getGlobalBounds().width / 2, background[i].getGlobalBounds().height / 2);
        background[i].setPosition(window.getSize().x / 2, window.getSize().y / 2);
    }

    range.setSize(sf::Vector2f(1920, window.getSize().y / 5 * 2));
    range.setFillColor(sf::Color::Yellow);
    range.setOrigin(range.getGlobalBounds().width / 2, range.getGlobalBounds().height / 2);
    range.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 100);
    outback.setTexture(&backgroundT[0]);
    BackGround.push_back(outback);
    for (int i = 0; i < 4; ++i) {
        background[i].setTexture(&backgroundT[i + 1]);
        BackGround.push_back(background[i]);
    }
    range.setTexture(&backgroundT[5]);
    BackGround.push_back(range);
}