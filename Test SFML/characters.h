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

	sf::Vector2f characterSize;
	float velocity;
	//jump
	bool isJumping;
	float gravity;
	float landingPOS;
	//Attack
	int power;
	float attack_CD;
	bool canAttack;
	float Timer_Attack;
	float Timer_Wait;
	int direction;
	float blood;
	bool isHit;
public:
	characters(sf::Vector2f size);
	void move(sf::Vector2i D, float deletaTime);
};

class enemy;

class mainPlayer : public characters
{
private:
	//animation
	sf::Texture texture_attack;
	sf::Texture texture_die;
	sf::Texture texture_hurt;
	sf::Texture texture_idle;
	sf::Texture texture_run;
	sf::Texture texture_walk;
	sf::Texture texture_jump;
	sf::Vector2u sizeOfTexture;
	sf::Vector2i current;
	sf::RectangleShape HPbarback;
	sf::RectangleShape HPbarinner;
	bool d_change;
	float manWidth;
	float weaponWidth;
	//Attack relative
	int KB;
	int hitdirection;

	void initHPbar();
	int updateHPbar(sf::RectangleShape& HPbar);
public:
	mainPlayer(std::string path, sf::Vector2f size);
	int Update(float deltaTime, std::vector<enemy>& monsters, int& actionstate);
	void Jump(float deletaTime);
	void Attack(std::vector<enemy>& monster);
	friend class Game;
	friend class enemy;
};

class enemy : public characters
{
public:
	//enemy sample prototypes
	class enemySample {
	private:
		sf::Texture texture_attack;
		sf::Texture texture_die;
		sf::Texture texture_hurt;
		sf::Texture texture_idle;
		sf::Texture texture_run;
	public:
		enemySample(std::string path);
		friend class enemy;
	};
	//sample
	static std::vector<enemySample> Samples;
private:
	//member
	sf::Texture* texture_attack_ptr;
	sf::Texture* texture_die_ptr;
	sf::Texture* texture_hurt_ptr;
	sf::Texture* texture_idle_ptr;
	sf::Texture* texture_run_ptr;
	int start_y, gap_y;

	bool d_change;
	sf::Vector2u sizeOfTexture;
	sf::Vector2u current;
	float manWidth;
	float weaponWidth;
	sf::Vector2f Chasing_point;
public:
	enemy(sf::Vector2f size, int enemyType);
	/*
	enemy::Samples.push_back(mon3);
	enemy::Samples.push_back(mon9);
	enemy::Samples.push_back(mon1);
	*/
	void Attack(mainPlayer& players);
	int Update(float deltaTime, mainPlayer& plyerOne);
	friend class mainPlayer;
};