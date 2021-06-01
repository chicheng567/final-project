#include "Game.h"
#include "characters.h"
Game::Game(std::string path):stateChange(1)
{
	state = Game::GameStates::Menu;
	font.loadFromFile(path);
	window.create(sf::VideoMode::getDesktopMode(), "works");
}
void Game::update()
{
	//clear all vectors
	Buttons.clear();
	BackGround.clear();
	shapes.clear();
	Texts.clear();

	if (state == Menu) {
		MainMenu();
	}
	else if (state == HE) {
		Ending(1);
	}
	else if (state == BE) {
		Ending(0);
	}
	else if (state == GameRunning) {
		gameStart();
	}
	stateChange = 0;
}
void Game::GameRun()
{
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (stateChange) {
			update();
		}
		if (state == GameRunning) {
			for (int i = 0; i < shapes.size(); ++i) {
				shapes.at(i).Update(clock.restart().asSeconds());
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				stateChange = 1;
				state = BE;
			}
		}
		else {
			mouseDetect();
		}

		//drawing UI
		window.clear(sf::Color(100, 100, 100));
		for (int i = 0; i < BackGround.size(); ++i) {
			window.draw(BackGround[i]);
		}
		for (int i = 0; i < Texts.size(); ++i) {
			window.draw(Texts[i]);
		}
		for (int i = 0; i < Buttons.size(); ++i) {
			window.draw(Buttons[i]);
		}
		for (int i = 0; i < shapes.size(); ++i) {
			window.draw(shapes[i].shape);
		}
		window.display();
	}
}
