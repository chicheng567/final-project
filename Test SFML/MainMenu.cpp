#include"Game.h"
void Game::MainMenu()
{
	sf::RectangleShape cover;
	sf::Texture* covertexture = new sf::Texture[1];
	covertexture->loadFromFile("./background/layers/battleground.png");
	cover.setTexture(covertexture);
	cover.setSize(sf::Vector2f(1920, window.getSize().y));
	cover.setOrigin(cover.getGlobalBounds().width / 2, cover.getGlobalBounds().height / 2);
	cover.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	sf::Text title("Legend Never Die", font, 100);
	sf::RectangleShape sword;
	sf::Texture* sword_T = new sf::Texture;
	sf::Vector2u warriorsize;
	sword_T->loadFromFile("./textures/weapons.png");
	sword.setTexture(sword_T);
	sword.setSize(sf::Vector2f(512, 512));
	sword.setPosition(1000, 350);
	sf::RectangleShape newGame;
	sf::RectangleShape Exit;
	sf::Texture* new_T = new sf::Texture;
	sf::Texture* con_T = new sf::Texture;
	sf::Texture* Exit_T = new sf::Texture;
	new_T->loadFromFile("./textures/new_button.png");
	Exit_T->loadFromFile("./textures/exit Button.png");
	newGame.setTexture(new_T);
	Exit.setTexture(Exit_T);
	//set title position
	title.setPosition(
		window.getSize().x / 2 - title.getGlobalBounds().width / 2, 100
	);
	//set buttoms position
	newGame.setPosition(title.getPosition().x - 180, title.getPosition().y + 300);
	Exit.setPosition(newGame.getPosition().x, newGame.getPosition().y + 300);

	BackGround.push_back(cover);
	Buttons.push_back(newGame);
	Buttons.push_back(Exit);
	BackGround.push_back(sword);
	Texts.push_back(title);
}