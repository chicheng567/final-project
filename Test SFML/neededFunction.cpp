#include "Game.h"
void Game::collision()
{
	sf::FloatRect range = BackGround.at(5).getGlobalBounds();
	sf::Vector2f playerPOS = players[0].shape.getPosition();
	
	if (!range.contains(playerPOS)) {
		//¤W¸I¼²
		if (playerPOS.y < range.top) {
			players[0].shape.move(0, range.top - playerPOS.y);
		}
		//¤U¸I¼²
		else if(playerPOS.y > range.top + range.height){
			players[0].shape.move(0, (range.top + range.height) - playerPOS.y);
		}
		//¥ª¸I¼²
		if (playerPOS.x < range.left) {
			players[0].shape.move(range.left - playerPOS.x, 0);
		}
		//¥k¸I¼²
		else if (playerPOS.x > range.left + range.width) {
			players[0].shape.move(range.left + range.width - playerPOS.x, 0);
		}
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
					state = GameRunning;
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
	players.clear();
	Texts.clear();
	monsters.clear();
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