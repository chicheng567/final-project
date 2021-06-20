#include "characters.h"
#include "Game.h"
void Game::gameStart()
{
    map.wave = 0;
    mainPlayer playerOne("./textures/knight3/", sf::Vector2f(565 / 2.5, 368 / 2.5));
    playerOne.shape.setPosition(500, 500);
    players.push_back(playerOne);  //create and push the character in the vector
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
        backgroundT[i + 1].setRepeated(1);
        background[i].setTexture(&backgroundT[i + 1]);
        BackGround.push_back(background[i]);
    }
    backgroundT[5].setRepeated(1);
    range.setTexture(&backgroundT[5]);
    BackGround.push_back(range);
    HPbar.push_back(playerOne.HPbarback);
    HPbar.push_back(playerOne.HPbarinner);
    //set the range
    this->range = range.getGlobalBounds();
    //push back sample for monster
    enemy::enemySample mon3("./textures/monster3/");
    enemy::enemySample mon9("./textures/monster9/");
    enemy::enemySample mon1("./textures/monster1/");
    enemy::enemySample boss7("./textures/monster7/");
    enemy::Samples.push_back(mon3);
    enemy::Samples.push_back(mon9);
    enemy::Samples.push_back(mon1);
    enemy::Samples.push_back(boss7);
}