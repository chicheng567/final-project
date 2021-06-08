#include "characters.h"
#include<stdio.h>
characters::characters(sf::Vector2f size) : totalTime(0), switchTime(0.1f), direction(1)
{
	shape.setSize(size);
}

mainPlayer::mainPlayer(std::string path, sf::Vector2f size) : characters(size), d_change(0)
{
	shape.setPosition(500, 500);
	texture_attack.loadFromFile(path + "knight1_attack.png");
	texture_die.loadFromFile(path + "knight1_die.png");
	texture_hurt.loadFromFile(path + "knight1_hurt.png");
	texture_idle.loadFromFile(path + "knight1_idle.png");
	texture_jump.loadFromFile(path + "knight1_jump.png");
	texture_walk.loadFromFile(path + "knight1_walk.png");
	texture_run.loadFromFile(path + "knight1_run.png");

	current = { 480 , 0 };
	sizeOfTexture.x = 565;
	sizeOfTexture.y = 368;
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
}

void mainPlayer::Update(float deltaTime)
{
	totalTime += deltaTime;
	switchTime = 0.1;
	shape.setTexture(&texture_idle);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		shape.setTexture(&texture_walk);
		shape.move(0, -1.5);
		switchTime = 0.05;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		shape.setTexture(&texture_walk);
		shape.move(0, 1.5);
		switchTime = 0.05;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		shape.setTexture(&texture_walk);
		shape.move(-1.5, 0);
		if (direction != -1) {
			direction = -1;
			d_change = 1;
		}
		switchTime = 0.05;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		shape.setTexture(&texture_walk);
		shape.move(1.5, 0);
		if (direction != 1) {
			direction = 1;
			d_change = 1;
		}
		switchTime = 0.05;
	}
	if (totalTime >= switchTime) {
		current.y = (current.y + 1) % 9;
		totalTime -= switchTime;
	}
	shape.setTextureRect(sf::IntRect(current.x + (direction == 1 ? 0 : sizeOfTexture.x), 676 * current.y + 100, sizeOfTexture.x * direction, sizeOfTexture.y));
	if (d_change) {
		shape.move(shape.getSize().x / 2 * direction, 0);
		d_change = 0;
	}
}