#include "characters.h"
#include <cmath>
#include<stdio.h>
//共通
characters::characters(sf::Vector2f size, float V, float blood_in) : Timer_animation(0), switchTime(0.1f), direction(1), characterSize(size), velocity(V), isJumping(0), gravity(0), blood(blood_in), canAttack(0), isHit(0)
{
	shape.setSize(size);
	canAttack = 1;
}

void characters::move(sf::Vector2i D, float deletaTime)
{
	float temp_V = velocity * deletaTime;	//v * t = x
	//斜移動，速度 * 根號2
	if (D.x * D.y) {
		double temp = sqrt(2.0);
		shape.move((float)D.x * temp_V / temp, (float)D.y * temp_V / temp);
	}
	else {
		shape.move((float)D.x * temp_V, (float)D.y * temp_V);
		if (isJumping) {
			landingPOS += (float)D.y * temp_V;
		}
	}
}
//玩家
mainPlayer::mainPlayer(std::string path, sf::Vector2f size, float V) : characters(size, V, 300), d_change(0)
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
	manWidth = characterSize.x / 2 - 20;
	weaponWidth = characterSize.x - manWidth;
	shape.setOrigin(manWidth , characterSize.y);
}

void mainPlayer::Update(float deltaTime, std::vector<enemy>& monsters)
{
	Timer_animation += deltaTime;
	if (!canAttack) {
		Timer_Attack += deltaTime;
		if (Timer_Attack <= 0.5 && Timer_Attack > 0.3) {
			Attack(monsters);
		}
		if (Timer_Attack >= 0.8) {
			canAttack = 1;
			for (int i = 0; i < monsters.size(); ++i) {
				monsters[i].isHit = 0;
			}
		}
	}
	if (canAttack || Timer_Attack >= 0.5) {	//0.5為跑完攻擊動畫所需時間
		sf::Vector2i temp;
		if (!isJumping) {
			shape.setTexture(&texture_idle);
			switchTime = 0.1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				temp.y = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				temp.y = 1;
			}
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
		//if jumping
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
			isJumping = 1;
			gravity = -300;
			shape.setTexture(&texture_jump);
			switchTime = 0.2;
			current.y = 0;
			landingPOS = shape.getPosition().y;
		}
		//if running
		if (temp.x || temp.y) {
			shape.setTexture(&texture_walk);
			velocity = 100;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				shape.setTexture(&texture_run);
				velocity = 300;
			}
			move(temp, deltaTime);
		}
		//校正回歸, 可command掉看後果
		//改變參考點
		if (d_change) {
			shape.setOrigin(shape.getOrigin().x - (weaponWidth - manWidth) * direction, characterSize.y);
			shape.move(direction * manWidth / 2, 0);
			d_change = 0;
		}
		//attack
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && canAttack) {
			canAttack = 0;
			switchTime = 0.05;
			Timer_Attack = 0;
			shape.setTexture(&texture_attack);
			current.y = 9;
		}
	}
	//regular Update
	Jump(deltaTime);
	if (Timer_animation >= switchTime) {
		current.y = (current.y + 1) % 10;
		Timer_animation -= switchTime;
	}
	shape.setTextureRect(sf::IntRect(current.x + (direction == 1 ? 0 : sizeOfTexture.x), 676 * current.y + 100, sizeOfTexture.x * direction, sizeOfTexture.y));// 676為step

}

//怪物
enemy::enemy(std::string path, sf::Vector2f size, float V) : characters(size, V, 100), d_change(0)
{
	Chasing_point = { 0, 0 };
	shape.setPosition(0, 500);
	texture_attack.loadFromFile(path + "monster3_attack.png");
	texture_die.loadFromFile(path + "monster3_die.png");
	texture_hurt.loadFromFile(path + "monster3_hurt.png");
	texture_idle.loadFromFile(path + "monster3_idle .png");
	texture_run.loadFromFile(path + "monster3_run.png");
	current = { 52, 0 };
	sizeOfTexture.x = 200;
	sizeOfTexture.y = 215;
	manWidth = characterSize.x / 2 - 20;
	weaponWidth = characterSize.x - manWidth;
	shape.setOrigin(manWidth, characterSize.y);
}

int enemy::Update(float deltaTime, mainPlayer& plyerOne)
{
	Timer_animation += deltaTime;
	if (blood > 0) {
		Chasing_point = plyerOne.shape.getPosition();
		if (plyerOne.isJumping) {
			Chasing_point.y = plyerOne.landingPOS;
		}
		Chasing_point.x -= plyerOne.direction * plyerOne.manWidth / 2;

		//我也不知道這段的數字在幹嘛，反正就是修復一些誤差
		if (direction * plyerOne.direction < 0) {
			Chasing_point.x += 30 * plyerOne.direction;
		}
		switchTime = 0.05;
		sf::Vector2i temp;
		shape.setTexture(&texture_idle);

		if (shape.getPosition().x - Chasing_point.x > 0) {
			if (direction != -1) {
				direction = -1;
				d_change = 1;
			}
			if (shape.getPosition().x - Chasing_point.x > weaponWidth) {
				shape.setTexture(&texture_run);
				temp.x = -1;
			}
		}
		else if (shape.getPosition().x - Chasing_point.x <= 0) {
			if (direction != 1) {
				direction = 1;
				d_change = 1;
			}
			if (Chasing_point.x - shape.getPosition().x > weaponWidth) {
				shape.setTexture(&texture_run);
				temp.x = 1;
			}
		}
		if (Chasing_point.y - shape.getPosition().y > 0) {
			temp.y = 1;
		}
		else if (Chasing_point.y - shape.getPosition().y < 0) {
			temp.y = -1;
		}

		if (temp.x || temp.y) {
			shape.setTexture(&texture_run);
			move(temp, deltaTime);
		}
		if (d_change) {
			shape.setOrigin(shape.getOrigin().x - (weaponWidth - manWidth) * direction, characterSize.y);
			shape.move(direction * manWidth / 2, 0);
			d_change = 0;
		}

	}
	else {
		shape.setTexture(&texture_die);
		if (current.y == 18) {
			return 1;
		}
	}

	//regular update
	if (Timer_animation >= switchTime) {
		current.y = (current.y + 1) % 19;
		Timer_animation -= switchTime;
	}
	shape.setTextureRect(sf::IntRect(current.x + (direction == 1 ? 0 : sizeOfTexture.x), 301 * current.y + 70, sizeOfTexture.x * direction, sizeOfTexture.y));
	return 0;
}