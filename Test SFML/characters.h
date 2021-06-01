#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include<iostream>
class characters
{
public:
	sf::RectangleShape shape;	//shape should be draw
	sf::Texture Texture;
protected:
	float totalTime;
	float switchTime; //the time for switching rect
	sf::IntRect TextureRect;
	sf::Vector2u characterSize;
public:
	characters(std::string path, sf::Vector2f size);
	virtual void Update(float deltaTime) = 0;
};


class mainPlayer : public characters
{
private:
	sf::Vector2u sizeOfTexture;
	sf::Vector2u current;
public:
	mainPlayer(std::string path, sf::Vector2f size);
	void Update(float deltaTime);
};