#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<vector>
#include"characters.h"
class Game
{
private:
	sf::Clock clock;
	int state;
	bool stateChange;
	sf::Vector2f mousePosition;
	enum GameStates {
		Menu=1, HE, BE, GameRunning, Pause
	};
	sf::Font font;
	sf::RenderWindow window;
	std::vector<sf::Text> Texts;
	std::vector<sf::Text> Buttons;
	std::vector<sf::RectangleShape> BackGround;
	std::vector<mainPlayer> shapes;
public:
	Game(std::string path);
	void update();	//update gameState
	void GameRun();
	//sub function
	void MainMenu();
	void Ending(int mode);
	void gameStart();
	void mouseDetect();
};