#include "Game.h"
#include "characters.h"
#include <cmath>

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

int mainPlayer::Update(float deltaTime, std::vector<enemy>& monsters, int& actionState)
{
	Timer_animation += deltaTime;
	shape.setTexture(&texture_idle);
	//判定攻擊
	if (!canAttack) {
		Timer_Attack += deltaTime;
		if (Timer_Attack <= 0.5 && Timer_Attack > 0.3 && !isHit) {
			Attack(monsters);
		}
		if (Timer_Attack >= 0.8) {
			canAttack = 1;
			for (int i = 0; i < monsters.size(); ++i) {
				monsters[i].isHit = 0;
			}
		}
	}
	//判定受傷擊退
	if (KB >= 150) {
		Timer_Wait += deltaTime;
		shape.setTexture(&texture_hurt);
		current.y = -1;
		switchTime = 0.05;
		KB = 0;
		if (hitdirection == -1) {
			d_change = 1;
			direction *= hitdirection;
			hitdirection = 0;
		}
	}
	if (blood > 0) {
		if (Timer_Wait && current.y != 9) {
			move(sf::Vector2i(-1 * direction, 0), deltaTime);
		}
		else {
			Timer_Wait = 0;
			if (canAttack || Timer_Attack >= 0.5) {    //0.5為跑完攻擊動畫所需時間
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
					actionState = Game::Action::jump;
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
				//attack
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
					actionState = Game::Action::attack;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && canAttack) {
					canAttack = 0;
					switchTime = 0.05;
					Timer_Attack = 0;
					shape.setTexture(&texture_attack);
					current.y = 9;
				}
			}
			Jump(deltaTime);
		}
	}
	else {
		shape.setTexture(&texture_die);
		if (current.y == 9) {
			return 1;
		}
	}

	//regular Update
	//校正回歸, 可command掉看後果
	//改變參考點
	if (d_change) {
		shape.setOrigin(shape.getOrigin().x - (weaponWidth - manWidth) * direction, characterSize.y);
		shape.move(direction * manWidth / 2, 0);
		d_change = 0;
	}
	if (Timer_animation >= switchTime) {
		current.y = (current.y + 1) % 10;
		Timer_animation -= switchTime;
	}
	shape.setTextureRect(sf::IntRect(current.x + (direction == 1 ? 0 : sizeOfTexture.x), 676 * current.y + 100, sizeOfTexture.x * direction, sizeOfTexture.y));// 676為step
	std::cout << shape.getPosition().x << " " << shape.getPosition().y << "\n";
	return 0;
}

//怪物
int enemy::Update(float deltaTime, mainPlayer& plyerOne)
{
	Timer_animation += deltaTime;
	if (!canAttack) {
		Timer_Attack += deltaTime;
		if (Timer_Attack <= 0.5 && Timer_Attack > 0.4 && !isHit) {
			Attack(plyerOne);
		}
		if (Timer_Attack >= 0.8) {
			canAttack = 1;
			plyerOne.isHit = 0;
		}
	}
	if (blood > 0) {
		//更新追蹤點
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
		//hurt
		if (isHit || (Timer_Wait > 0 && Timer_Wait < 0.5)) {
			if (isHit) {
				shape.setTexture(texture_hurt_ptr);
				move(sf::Vector2i(-1 * direction, 0), deltaTime);
			}
			Timer_Wait += deltaTime;
		}
		//can move
		else {
			Timer_Wait = 0;
			if (shape.getPosition().x - Chasing_point.x > 0) {
				if (direction != -1) {
					direction = -1;
					d_change = 1;
				}
				if (shape.getPosition().x - Chasing_point.x > weaponWidth) {
					shape.setTexture(texture_run_ptr);
					temp.x = -1;
				}
			}
			else if (shape.getPosition().x - Chasing_point.x <= 0) {
				if (direction != 1) {
					direction = 1;
					d_change = 1;
				}
				if (Chasing_point.x - shape.getPosition().x > weaponWidth) {
					shape.setTexture(texture_run_ptr);
					temp.x = 1;
				}
			}
			if (Chasing_point.y - shape.getPosition().y > 10) {
				temp.y = 1;
			}
			else if (Chasing_point.y - shape.getPosition().y < -10) {
				temp.y = -1;
			}

			if (temp.x || temp.y) {
				shape.setTexture(texture_run_ptr);
				move(temp, deltaTime);
			}
			else {
				if (canAttack && plyerOne.blood > 0) {
					canAttack = 0;
					switchTime = 0.05;
					Timer_Attack = 0;
					shape.setTexture(texture_attack_ptr);
					current.y = 18;
				}
			}
			if (d_change) {
				shape.setOrigin(shape.getOrigin().x - (weaponWidth - manWidth) * direction, characterSize.y);
				shape.move(direction * manWidth / 2, 0);
				d_change = 0;
			}
		}
	}
	else {
		shape.setTexture(texture_die_ptr);
		if (current.y == 18) {
			return 1;
		}
	}
	//regular update
	if (Timer_animation >= switchTime) {
		current.y = (current.y + 1) % 19;
		Timer_animation -= switchTime;
	}
	
	shape.setTextureRect(sf::IntRect(current.x + (direction == 1 ? 0 : sizeOfTexture.x), gap_y * current.y + start_y, sizeOfTexture.x * direction, sizeOfTexture.y));
	return 0;
}

void mainPlayer::Jump(float deletaTime)
{
	if (gravity) {
		gravity += deletaTime * 600;
		shape.move(0, gravity * deletaTime);
	}
	if (gravity >= 300) {
		isJumping = 0;
		gravity = 0;
	}
}

void mainPlayer::Attack(std::vector<enemy>& monsters)
{
	for (int i = 0; i < monsters.size(); ++i) {
		if (direction * monsters[i].direction < 0 && !monsters[i].isHit) {
			if (fabs(monsters[i].shape.getPosition().x - shape.getPosition().x) <= this->weaponWidth - 10
				&& fabs(monsters[i].shape.getPosition().y - shape.getPosition().y) <= 20) {
				monsters[i].blood -= power;
				monsters[i].isHit = 1;
				if (monsters[i].blood <= 0) {
					monsters[i].current.y = 0;
				}
			}
		}
	}
}

void enemy::Attack(mainPlayer& players) {
	if (!players.isHit) {
		if (direction * players.direction < 0) {
			players.hitdirection = 1;
		}
		else {
			players.hitdirection = -1;
		}
		players.blood -= power;
		players.KB += power;
		players.isHit = 1;
		if (players.blood <= 0) {
			players.current.y = 0;
		}
	}
}