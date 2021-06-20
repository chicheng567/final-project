#include "Game.h"
void Game::collision(float deletaTime)
{
    bool backMove = 0;
    sf::FloatRect range = this->range;
    sf::Vector2f playerPOS = players[0].shape.getPosition();
    if (monsters.empty() && boss_vec.empty()) {
        backMove = 1;
        range.width = this->range.width * 3 / 5;
    }
    if (!range.contains(playerPOS)) {
        //¤W¸I¼²
        if (playerPOS.y < range.top && !players[0].isJumping) {
            players[0].shape.move(0, range.top - playerPOS.y);
        }
        //¤U¸I¼²
        else if (playerPOS.y > range.top + range.height) {
            players[0].shape.move(0, (range.top + range.height) - playerPOS.y);
        }
        //¥ª¸I¼²
        if (playerPOS.x < range.left) {
            players[0].shape.move(range.left - playerPOS.x, 0);
        }
        //¥k¸I¼²
        else if (playerPOS.x > range.left + range.width) {
            players[0].shape.move(range.left + range.width - playerPOS.x, 0);
            if (monsters.empty() && boss_vec.empty()) {
                moving_backGround(deletaTime);
            }
        }
    }
}
void Game::moving_backGround(float deletaTime)
{
    float D_X = players[0].velocity * deletaTime * 2;
    sf::IntRect temp;
    temp = BackGround.at(1).getTextureRect();
    temp.left += D_X;
    temp.left %= temp.width;
    if (BackGround[1].getTextureRect().left > temp.left) {
        sponse_monster();
    }
    for (int i = 1; i < BackGround.size(); ++i) {
        temp = BackGround.at(i).getTextureRect();
        temp.left += D_X;
        temp.left %= temp.width;
        BackGround.at(i).setTextureRect(temp);
    }

}

void Game::mouseDetect()
{
    //determine state
    sf::Vector2f originSize;
    sf::Vector2f biggerSize;
    if (state == Game::GameStates::Menu) {
        originSize.x = 296;
        originSize.y = 61;
        biggerSize.x = 350;
        biggerSize.y = 70;
    }
    else {
        originSize.x = 100;
        originSize.y = 100;
        biggerSize.x = 150;
        biggerSize.y = 150;
    }
    mousePosition = { (float)sf::Mouse::getPosition(window).x , (float)sf::Mouse::getPosition(window).y };
    for (int i = 0; i < Buttons.size(); ++i) {
        if (Buttons.at(i).getGlobalBounds().contains(mousePosition)) {
            Buttons.at(i).setSize(biggerSize);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                stateChange = 1;
                if (i == 0) {
                    state = Load;
                }
                else if (state == Pause && i == 1) {
                    state = Menu;
                }
                else {
                    window.close();
                }
            }
        }
        else {
            Buttons.at(i).setSize(originSize);
        }
    }
}

void Game::clearVectors()
{
    //clear Textures
    for (int i = 0; i < Buttons.size(); ++i)
    {
        if (Buttons[i].getTexture() != nullptr) {
            delete Buttons.at(i).getTexture();
            Buttons.at(i).setTexture(0);
        }
    }
    if (!BackGround.empty() && BackGround.at(0).getTexture()) {
        delete[] BackGround.at(0).getTexture();
    }
    //clear all vectors
    Buttons.clear();
    BackGround.clear();
    HPbar.clear();
    players.clear();
    Texts.clear();
    monsters.clear();
    boss_vec.clear();
}
void Game::clear_render()
{
    for (int i = 0; i < render_back.size(); ++i)
    {
        if (render_back.at(i).getTexture()) {
            delete render_back.at(i).getTexture();
            render_back.at(i).setTexture(0);
        }
    }
    for (int i = 0; i < Buttons.size(); ++i) {
        if (Buttons.at(i).getTexture()) {
            delete Buttons.at(i).getTexture();
            Buttons.at(i).setTexture(0);
        }
    }
    render_back.clear();
    Texts.clear();
    Buttons.clear();
}