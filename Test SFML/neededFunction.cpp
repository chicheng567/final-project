#include "Game.h"
void Game::mouseDetect()
{
	mousePosition = { (float)sf::Mouse::getPosition(window).x , (float)sf::Mouse::getPosition(window).y };
	for (int i = 0; i < Buttons.size(); ++i) {
		if (Buttons.at(i).getGlobalBounds().contains(mousePosition)) {
			Buttons.at(i).setCharacterSize(60);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				stateChange = 1;
				if (Buttons.at(i).getString() == "YES"
					|| Buttons.at(i).getString() == "newGame") {
					state = GameRunning;
				}
				else {
					window.close();
				}
			}
		}
		else {
			Buttons.at(i).setCharacterSize(50);
		}
	}
}
