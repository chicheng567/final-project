#include "characters.h"
#include <cmath>
#include<stdio.h>
//共通
characters::characters(sf::Vector2f size, float V) : Timer_animation(0), switchTime(0.1f), direction(1), characterSize(size), velocity(V)
{
	shape.setSize(size);
}

void characters::move(sf::Vector2i D, float deletaTime)
{
	float temp_V = velocity * deletaTime;	//v * t = x
	std::cout << temp_V << "\n";
	//斜移動，速度 * 根號2
	if (D.x * D.y) {
		double temp = sqrt(2.0);
		shape.move((float)D.x * temp_V / temp, (float)D.y * temp_V / temp);
	}
	else {
		shape.move((float)D.x * temp_V, (float)D.y * temp_V);
	}
}
//玩家
mainPlayer::mainPlayer(std::string path, sf::Vector2f size, float V) : characters(size, V), d_change(0)
{
	shape.setPosition(500, 500);
	texture_attack.loadFromFile(path + "knight3_attack.png");
	texture_die.loadFromFile(path + "knight3_die.png");
	texture_hurt.loadFromFile(path + "knight3_hurt.png");
	texture_idle.loadFromFile(path + "knight3_idle.png");
	texture_jump.loadFromFile(path + "knight3_jump.png");
	texture_walk.loadFromFile(path + "knight3_walk.png");
	texture_run.loadFromFile(path + "knight3_run.png");
	current = { 480 , 0 };
	sizeOfTexture.x = 565;
	sizeOfTexture.y = 368;
	manWidth = characterSize.x / 2 - 30;
	weaponWidth = characterSize.x - manWidth;
	shape.setOrigin(manWidth, characterSize.y);
}

void mainPlayer::Update(float deltaTime)
{
	Timer_animation += deltaTime;
	switchTime = 0.1;
	shape.setTexture(&texture_idle);
	sf::Vector2i temp;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		temp.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		temp.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		temp.x = -1;
		if (direction != -1) {
			direction = -1;
			d_change = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		temp.x = 1;
		if (direction != 1) {
			direction = 1;
			d_change = 1;
		}
	}
	if (temp.x || temp.y) {
		shape.setTexture(&texture_walk);
		velocity = 100;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			shape.setTexture(&texture_run);
			velocity = 300;
		}
		move(temp, deltaTime);
	}

	if (Timer_animation >= switchTime) {
		current.y = (current.y + 1) % 9;
		Timer_animation -= switchTime;
	}
	shape.setTextureRect(sf::IntRect(current.x + (direction == 1 ? 0 : sizeOfTexture.x), 676 * current.y + 100, sizeOfTexture.x * direction, sizeOfTexture.y));// 676為step
	
	//校正回歸, 可command掉看後果
	//改變參考點
	if (d_change) {
		shape.setOrigin(shape.getOrigin().x - (weaponWidth - manWidth)*direction , characterSize.y);
		shape.move(direction * manWidth / 2, 0);
		d_change = 0;
	}
}

//怪物
enemy::enemy(std::string path, sf::Vector2f size, float V) : characters(size, V)
{
	shape.setPosition(900, 500);
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
}

void enemy::Update(float deltaTime, mainPlayer& plyerOne) {
    
    if (plyerOne.shape.getPosition().x - shape.getPosition().x > 0) {
		move(sf::Vector2i(1, 0), deltaTime);
    }
    if (plyerOne.shape.getPosition().x - shape.getPosition().x < 0) {
         move(sf::Vector2i(-1, 0), deltaTime);
    }
    if (plyerOne.shape.getPosition().y - shape.getPosition().y > 0) {
         move(sf::Vector2i(0, 1), deltaTime);
    }
    if (plyerOne.shape.getPosition().y - shape.getPosition().y < 0) {
        move(sf::Vector2i(0, -1), deltaTime);
    }
}


