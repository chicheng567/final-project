#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
#include<vector>
#include"characters.h"

class Game
{
private:
	//MAP
	class Map {
	private:
		int wave;
		std::vector<int> monster3;
		std::vector<int> monster9;
		std::vector<int> monster1;
	public:
		Map();
		int wave_detect(int monsterNUM);
		friend class Game;
	};
	//music
	enum MusicStates {
		Playing = 1, Lose, Beginning, Stop, Win
	};
	int musicstate;

	sf::Clock clock;
	int state;
	bool stateChange;
	sf::Vector2f mousePosition;
	enum GameStates {
		Menu = 1, HE, BE, GameRunning, Pause, Load
	};
	sf::Font font;
	sf::RenderWindow window;
	std::vector<sf::RectangleShape> render_back;
	std::vector<sf::Text> Texts;
	std::vector<sf::RectangleShape> Buttons;
	std::vector<sf::RectangleShape> BackGround;
	std::vector<mainPlayer> players;
	std::vector<enemy> monsters;
	std::vector<boss> boss_vec;
	Map map;
//ADD
	float Timer_animation;
	float switchTime;
	sf::Vector2u current;
	std::vector<sf::RectangleShape> ad;
public:
	enum Action {
		attack = 1, jump
	};
	int actionState;
	//public properties
	sf::Rect<float> range;
	std::vector<sf::RectangleShape> HPbar;
	//methods and constructor
	Game(std::string path);
	void updateState(); //update gameState
	void GameRun();
	//Menus construct function
	void gameStart();
	void MainMenu();
	void Ending(int mode);
	void PauseMenu(float deltatime, std::vector<sf::RectangleShape>& ads);
	void updateAD(float deltaTime, sf::RectangleShape& AD); //update pause ad
	void Loading();
	//needed function
	void moving_backGround(float deletaTime);
	void collision(float deletaTime);
	void mouseDetect();
	void clearVectors();
	void clear_render();
	//MAP methods
	void sponse_monster();
};