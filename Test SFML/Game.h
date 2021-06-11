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
	std::vector<sf::RectangleShape> render_back;
	std::vector<sf::Text> Texts;
	std::vector<sf::RectangleShape> Buttons;
	std::vector<sf::RectangleShape> BackGround;
	std::vector<mainPlayer> players;
	std::vector<enemy> monsters;
public:
	Game(std::string path);
	void updateState();	//update gameState
	void GameRun();
	//Menus construct function
	void gameStart();
	void MainMenu();
	void Ending(int mode);
	void PauseMenu();
	//needed function
	void collision();
	void mouseDetect();
	void clearVectors();
	void clear_render();
};