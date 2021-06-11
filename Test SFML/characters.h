#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include<iostream>
class characters
{
public:
	sf::RectangleShape shape; //shape should be draw
	sf::Texture Texture;
protected:
	int direction;
	//timers
	float Timer_animation;
	float switchTime;//the time for switching rect
	sf::Texture texture_attack;
	sf::Texture texture_die;
	sf::Texture texture_hurt;
	sf::Texture texture_idle;
	sf::Texture texture_walk;
	sf::Vector2f characterSize;
	float velocity;
public:
	characters(sf::Vector2f size, float V);
	void move(sf::Vector2i D, float deletaTime);
};


class mainPlayer : public characters
{
private:
	bool d_change;
	sf::Vector2u sizeOfTexture;
	sf::Vector2u current;
	sf::Texture texture_jump;
	sf::Texture texture_run;
	float manWidth;
	float weaponWidth;
public:
	mainPlayer(std::string path, sf::Vector2f size, float V);
	void Update(float deltaTime);
};

class enemy : public characters
{
public:
	enemy(std::string path, sf::Vector2f size, float V);
	void Update(float deltaTime, mainPlayer& plyerOne);
	void Attack(float blood, mainPlayer& plyerOne);
};

