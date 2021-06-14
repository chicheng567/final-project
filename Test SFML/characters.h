#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include<iostream>
class characters
{
public:
	sf::RectangleShape shape; //shape should be draw
protected:
	//timers
	float Timer_animation;
	float switchTime;//the time for switching rect
	sf::Texture texture_attack;
	sf::Texture texture_die;
	sf::Texture texture_hurt;
	sf::Texture texture_idle;
	sf::Texture texture_run;
	sf::Vector2f characterSize;
	float velocity;
	//jump
	bool isJumping;
	float gravity;
	float landingPOS;
	//Attack
	bool canAttack;
	float Timer_Attack;
	int direction;
	float blood;
	bool isHit;
public:
	characters(sf::Vector2f size, float V, float blood_in);
	void move(sf::Vector2i D, float deletaTime);
};

class enemy;

class mainPlayer : public characters
{
private:
	//animation
	sf::Vector2u sizeOfTexture;
	sf::Vector2u current;
	sf::Texture texture_walk;
	sf::Texture texture_jump;
	bool d_change;
	float manWidth;
	float weaponWidth;
public:
	mainPlayer(std::string path, sf::Vector2f size, float V);
	void Update(float deltaTime, std::vector<enemy>&monsters);
	void Jump(float deletaTime);
	void Attack(std::vector<enemy>&monster);
	friend class Game;
	friend class enemy;
};

class enemy : public characters
{
private:
	bool d_change;
	sf::Vector2u sizeOfTexture;
	sf::Vector2u current;
	float manWidth;
	float weaponWidth;
	sf::Vector2f Chasing_point;
public:
	enemy(std::string path, sf::Vector2f size, float V);
	int Update(float deltaTime, mainPlayer& plyerOne);
	friend class mainPlayer;
};
