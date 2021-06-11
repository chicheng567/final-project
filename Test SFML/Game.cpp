#include "Game.h"
#include "characters.h"
Game::Game(std::string path) :stateChange(1)
{
	state = Game::GameStates::Menu;
	font.loadFromFile(path);
	window.create(sf::VideoMode::getDesktopMode(), "works");
}
void Game::updateState()
{

	if (state == Menu) {
		clearVectors();
		clear_render();
		MainMenu();
	}
	else if (state == HE) {
		clearVectors();
		Ending(1);
	}
	else if (state == BE) {
		clearVectors();
		Ending(0);
	}
	else if (state == GameRunning) {
		clear_render();
		if (!players.size()) {
			gameStart();
		}

	}
	else if (state == Pause) {
		PauseMenu();
	}
	clock.restart();
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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				if (state == GameRunning) {
					stateChange = 1;
					state = Pause;
				}
				else if (state == Pause) {
					stateChange = 1;
					state = GameRunning;
				}
			}
		}
		//state construct
		if (stateChange) {
			updateState();
		}

		//update control
		if (state == GameRunning) {
			for (int i = 0; i < monsters.size(); ++i) {
				monsters.at(i).Update(clock.getElapsedTime().asSeconds(), players.at(0));
			}
			for (int i = 0; i < players.size(); ++i) {
				players.at(i).Update(clock.restart().asSeconds());
				collision();
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
		for (int i = 0; i < players.size(); ++i) {
			window.draw(players[i].shape);
		}
		for (int i = 0; i < monsters.size(); ++i) {
			window.draw(monsters[i].shape);
		}
		for (int i = 0; i < render_back.size(); ++i) {
			window.draw(render_back[i]);
		}
		for (int i = 0; i < Buttons.size(); ++i) {
			window.draw(Buttons[i]);
		}
		for (int i = 0; i < Texts.size(); ++i) {
			window.draw(Texts[i]);
		}
		window.display();
	}
}
