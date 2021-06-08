#include"Game.h"
void Game::MainMenu()
{
	sf::Text title("Our game", font, 100);
	sf::RectangleShape newGame;
	sf::RectangleShape continueB;
	sf::RectangleShape Exit;
	sf::Texture* new_T = new sf::Texture;
	sf::Texture* con_T = new sf::Texture;
	sf::Texture* Exit_T = new sf::Texture;
	new_T->loadFromFile("./textures/new_button.png");
	con_T->loadFromFile("./textures/continue.png");
	Exit_T->loadFromFile("./textures/exit Button.png");
	newGame.setTexture(new_T);
	continueB.setTexture(con_T);
	Exit.setTexture(Exit_T);
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
}