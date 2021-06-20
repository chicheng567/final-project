#include "Game.h"
void Game::PauseMenu(float deltatime, std::vector<sf::RectangleShape>& ads)
{
    if (state == Pause) {
        sf::RectangleShape Pause_background(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
        Pause_background.setFillColor(sf::Color(100, 100, 100, 220));

        sf::RectangleShape selectWindow(sf::Vector2f(1300, 800));
        selectWindow.setPosition(window.getSize().x / 2 - 650, window.getSize().y / 2 - 400);
        sf::Texture* windowBackTexture = new sf::Texture;
        windowBackTexture->loadFromFile("./textures/pauseMenu.png");
        selectWindow.setTexture(windowBackTexture);

        //Texts
        sf::Clock clock;
        sf::Text title("Game Pause", font, 80);
        title.setFillColor(sf::Color::Black);
        title.setPosition(selectWindow.getPosition().x + 300, selectWindow.getPosition().y + 200);

        //Buttons
        sf::RectangleShape Resumn;
        sf::RectangleShape BackToMenu;
        sf::Texture* RT = new sf::Texture;
        sf::Texture* BT = new sf::Texture;
        RT->loadFromFile("./textures/resumn_button.png");
        BT->loadFromFile("./textures/back_button.png");
        Resumn.setTexture(RT);
        BackToMenu.setTexture(BT);
        Resumn.setPosition(title.getPosition().x + 80, title.getPosition().y + 250);
        BackToMenu.setPosition(title.getPosition().x + 320, title.getPosition().y + 250);

        //advertisement
        sf::RectangleShape AD;
        sf::Texture* AD_T = new sf::Texture;
        AD_T->loadFromFile("./textures/gambling.png");
        AD_T->setRepeated(true);
        AD.setTexture(AD_T);
        AD.setSize(sf::Vector2f(316.81, 130.1));
        AD.setPosition(title.getPosition().x + 220, title.getPosition().y + 375);
        AD.setTextureRect(sf::IntRect(0, 321.2 * 0, 760, 321.2));

        //push
        Texts.push_back(title);
        render_back.push_back(Pause_background);
        render_back.push_back(selectWindow);
        Buttons.push_back(Resumn);
        Buttons.push_back(BackToMenu);
        render_back.push_back(AD);
    }
}