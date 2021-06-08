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
	float totalTime;
	float switchTime;//the time for switching rect
	sf::Texture texture_attack;
	sf::Texture texture_die;
	sf::Texture texture_hurt;
	sf::Texture texture_idle;
	sf::Texture texture_walk;
	sf::IntRect TextureRect;
	sf::Vector2u characterSize;
public:
	characters(sf::Vector2f size);
};


class mainPlayer : public characters
{
private:
	bool d_change;
	sf::Vector2u sizeOfTexture;
	sf::Vector2u current;
	sf::Texture texture_jump;
	sf::Texture texture_run;
public:
	mainPlayer(std::string path, sf::Vector2f size);
	void Update(float deltaTime);
};