#include "characters.h"
#include"Game.h"
#include <cmath>
#include<stdio.h>
//共通
characters::characters(sf::Vector2f size) : Timer_animation(0), switchTime(0.1f), direction(1), characterSize(size), isJumping(0), gravity(0), canAttack(0), isHit(0), Timer_Wait(0)
{
	shape.setSize(size);
	canAttack = 1;
	Timer_Attack = 0;
}

//玩家
mainPlayer::mainPlayer(std::string path, sf::Vector2f size) : characters(size), d_change(0), KB(0)
{
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
	shape.setOrigin(manWidth, characterSize.y);
	blood = 450;
	velocity = 100;
	power = 50;
	shape.setTexture(&texture_idle);
	initHPbar();
}

void mainPlayer::initHPbar() {
	float width = 300.f;
	float height = 50.f;
	float x = 20.f;
	float y = 20.f;

	HPbarback.setSize(sf::Vector2f(width, height));
	HPbarback.setFillColor(sf::Color(50, 50, 50, 200));
	HPbarback.setPosition(x, y);

	HPbarinner.setSize(sf::Vector2f(width, height));
	HPbarinner.setFillColor(sf::Color(250, 20, 20, 200));
	HPbarinner.setPosition(HPbarback.getPosition());
}

int mainPlayer::updateHPbar(sf::RectangleShape& HPbar) {
	float width = 300.f * (blood / 450);
	float height = 50.f;

	HPbar.setSize(sf::Vector2f(width, height));
	return 0;
}

//怪物
enemy::enemySample::enemySample(std::string path)
{
	texture_attack.loadFromFile(path + "attack.png");
	texture_die.loadFromFile(path + "die.png");
	texture_hurt.loadFromFile(path + "hurt.png");
	texture_run.loadFromFile(path + "run.png");
}
std::vector<enemy::enemySample> enemy::Samples;
enemy::enemy(sf::Vector2f size, int enemyType) : characters(size), d_change(0)
{
	if (enemyType == 0) {
		current = { 52, 0 };
		sizeOfTexture.x = 200;
		sizeOfTexture.y = 215;
		manWidth = characterSize.x / 2 - 20;
		gap_y = 301;
		start_y = 70;
		blood = 100;
		power = 50;
		velocity = 100;
	}
	else if (enemyType == 1) {
		current = { 40, 0 };
		sizeOfTexture.x = 190;
		sizeOfTexture.y = 200;
		manWidth = characterSize.x / 2 - 20;
		gap_y = 267;
		start_y = 50;
		blood = 150;
		power = 100;
		velocity = 80;
	}
	else if (enemyType == 2) {
		current = { 52, 0 };
		sizeOfTexture.x = 200;
		sizeOfTexture.y = 215;
		manWidth = characterSize.x / 2 - 20;
		gap_y = 285;
		start_y = 60;
		blood = 100;
		velocity = 200;
		power = 80;
	}

	weaponWidth = characterSize.x - manWidth;
	shape.setOrigin(manWidth, characterSize.y);
	//set Textures
	texture_attack_ptr = &Samples[enemyType].texture_attack;
	texture_die_ptr = &Samples[enemyType].texture_die;
	texture_hurt_ptr = &Samples[enemyType].texture_hurt;
	texture_run_ptr = &Samples[enemyType].texture_run;
}
