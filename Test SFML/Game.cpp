#include "Game.h"
#include "characters.h"
Game::Game(std::string path) :stateChange(1)
{
	state = Game::GameStates::Menu;
	font.loadFromFile(path);
	window.create(sf::VideoMode::getDesktopMode(), "works", sf::Style::Fullscreen);
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
		if (!shapes.size()) {
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
		if (stateChange) {
			updateState();
		}
		//Do action for any state
		if (state == GameRunning) {
			for (int i = 0; i < shapes.size(); ++i) {
				shapes.at(i).Update(clock.restart().asSeconds());
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
		for (int i = 0; i < shapes.size(); ++i) {
			window.draw(shapes[i].shape);
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
