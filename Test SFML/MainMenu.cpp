#include"Game.h"
void Game::MainMenu()
{
	Texts.clear();
	Buttons.clear();

	sf::Text title("Our game", font, 100);
	sf::Text newGame("newGame", font, 50);
	sf::Text continueB("continue", font, 50);
	sf::Text Exit("exit", font, 50);
	//set title position
	title.setPosition(
		window.getSize().x / 2 - title.getGlobalBounds().width / 2, 100
	);
	//set buttoms position
	newGame.setPosition(title.getPosition().x - 180, title.getPosition().y + 300);
	continueB.setPosition(newGame.getPosition().x, newGame.getPosition().y + 150);
	Exit.setPosition(newGame.getPosition().x, newGame.getPosition().y + 300);

	Buttons.push_back(newGame);
	Buttons.push_back(continueB);
	Buttons.push_back(Exit);
	Texts.push_back(title);
	stateChange = 1;
}