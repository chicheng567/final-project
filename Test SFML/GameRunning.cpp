#include "characters.h"
#include "Game.h"
void Game::gameStart()
{
    mainPlayer plyerOne("./textures/pacman_from_philippines.png", sf::Vector2f(100, 150));
    shapes.push_back(plyerOne);  //creat and push the character in the vector
    shapes[0].shape.setTexture(&shapes[0].Texture);
    sf::RectangleShape  shape, range;
    shape.setSize(sf::Vector2f(1600, window.getSize().y));
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
    shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    std::cout << window.getSize().y << std::endl;

    range.setSize(sf::Vector2f(1600, window.getSize().y / 5 * 2));
    range.setFillColor(sf::Color::Yellow);
    range.setOrigin(range.getGlobalBounds().width / 2, range.getGlobalBounds().height / 2);
    range.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 200);
    BackGround.push_back(shape);
    BackGround.push_back(range);
}