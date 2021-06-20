#include "Game.h"
#include "characters.h"
#include<thread>
Game::Game(std::string path) :stateChange(1), switchTime(0.005f)
{
	state = Game::GameStates::Menu;
	font.loadFromFile(path);
	window.create(sf::VideoMode::getDesktopMode(), "works", sf::Style::Fullscreen);
}
void Game::updateState()
{
	float deltatime;
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
	else if (state == Load) {
		clearVectors();
		Loading();
	}
	else if (state == GameRunning) {
		clear_render();
		if (!players.size()) {
			gameStart();
		}

	}
	else if (state == Pause) {
		deltatime = clock.restart().asSeconds();
		PauseMenu(deltatime, ad);
	}
	clock.restart();
	stateChange = 0;
}
void Game::updateAD(float deltaTime, sf::RectangleShape& AD) {
	Timer_animation += deltaTime;
	switchTime = 1;
	if (Timer_animation >= switchTime) {
		current.y = (current.y + 1) % 5;
		Timer_animation -= switchTime;
	}
	AD.setTextureRect(sf::IntRect(0, 321.2 * current.y, 760, 321.2));
}

void Game::GameRun()
{
	float deltatime;
	sf::Music music, BEmusic, opmusic, HEmusic, pausemusic;
	sf::Sound attackmusic, jumpmusic;
	sf::SoundBuffer attackmusicbuffer, jumpmusicbuffer;
	opmusic.openFromFile("./music/opening.ogg");
	opmusic.setVolume(50);
	opmusic.setLoop(true);
	music.openFromFile("./music/bgm.ogg");
	music.setVolume(50);
	music.setLoop(true);
	pausemusic.openFromFile("./music/pausemusic.ogg");
	pausemusic.setVolume(10);
	BEmusic.openFromFile("./music/deadmusic.ogg");
	BEmusic.setVolume(50);
	BEmusic.setLoop(true);
	HEmusic.openFromFile("./music/winning.ogg");
	HEmusic.setVolume(10);
	HEmusic.setLoop(true);
	attackmusicbuffer.loadFromFile("./music/playerattack.ogg");
	attackmusic.setBuffer(attackmusicbuffer);
	attackmusic.setVolume(50);
	jumpmusicbuffer.loadFromFile("./music/jumping.ogg");
	jumpmusic.setBuffer(jumpmusicbuffer);
	jumpmusic.setVolume(100);

	float DeletaTime;
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

		if (state == Load) {
			stateChange = 1;
			state = GameRunning;
		}

		//update control
		if (state == GameRunning) {
			musicstate = Playing;
			DeletaTime = clock.restart().asSeconds();
			for (int i = 0; i < monsters.size(); ++i) {
				if (monsters.at(i).Update(DeletaTime, players.at(0))) {
					monsters.erase(monsters.begin() + i);
					i--;
				}
			}
			if (!boss_vec.empty()) {
				if (boss_vec.at(0).Update(DeletaTime, players.at(0))) {
					state = HE;
					stateChange = 1;
				}
			}

			for (int i = 0; i < players.size(); ++i) {
				if (players.at(i).Update(DeletaTime, monsters,boss_vec, actionState) || players.at(i).updateHPbar(HPbar[1])) {
					state = BE;
					stateChange = 1;
				}
				collision(DeletaTime);
			}
		}
		else {
			mouseDetect();
		}

		if (state == Menu) {
			musicstate = Beginning;
		}
		if (state == Pause) {
			musicstate = Stop;
			updateAD(DeletaTime, render_back[2]);
		}
		if (state == BE) {
			musicstate = Lose;
		}
		if (state == HE) {
			musicstate = Win;
		}

		//check wave is complete
		if (!players.empty() && map.wave_detect(monsters.size())) {
			players.at(0).KB = 0;
		}

		//music update
		if (musicstate == Playing && (music.getStatus() == music.Stopped || music.getStatus() == music.Paused)) {
			BEmusic.stop();
			opmusic.stop();
			pausemusic.stop();
			music.play();
		}
		else if (musicstate == Stop && pausemusic.getStatus() == pausemusic.Stopped) {
			music.pause();
			pausemusic.play();
		}
		else if (musicstate == Lose && BEmusic.getStatus() == BEmusic.Stopped) {
			music.stop();
			BEmusic.play();
		}
		else if (musicstate == Win && HEmusic.getStatus() == HEmusic.Stopped) {
			music.stop();
			HEmusic.play();
		}
		else if (musicstate == Beginning && opmusic.getStatus() == opmusic.Stopped) {
			music.stop();
			pausemusic.stop();
			opmusic.play();

		}
		//else if(musicstate == )
		else if (musicstate == 0 && (music.getStatus() != music.Stopped || BEmusic.getStatus() != BEmusic.Stopped || opmusic.getStatus() != opmusic.Stopped || HEmusic.getStatus() != HEmusic.Stopped || pausemusic.getStatus() != pausemusic.Stopped)) {
			BEmusic.stop();
			HEmusic.stop();
			music.stop();
			pausemusic.stop();
			opmusic.stop();
		}
		if (actionState == attack) {
			attackmusic.play();
			actionState = 0;
		}
		if (actionState == jump) {
			jumpmusic.play();
			actionState = 0;
		}



		//drawing UI
		window.clear(sf::Color::Black);
		for (int i = 0; i < BackGround.size(); ++i) {
			window.draw(BackGround[i]);
		}
		for (int i = 0; i < HPbar.size(); ++i) {
			window.draw(HPbar[i]);
		}
		for (int i = 0; i < players.size(); ++i) {
			window.draw(players[i].shape);
		}
		for (int i = 0; i < monsters.size(); ++i) {
			window.draw(monsters[i].shape);
		}
		if (!boss_vec.empty()) {
			window.draw(boss_vec.at(0).shape);
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