#include "Game.h"
void Game::PauseMenu()
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

		//push
		Texts.push_back(title);
		render_back.push_back(Pause_background);
		render_back.push_back(selectWindow);
		Buttons.push_back(Resumn);
		Buttons.push_back(BackToMenu);
	}
}