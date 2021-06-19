#include "Game.h"
#include "characters.h"
#include <cmath>

void characters::move(sf::Vector2i D, float deletaTime)
{
	float temp_V = velocity * deletaTime;	//v * t = x
	//�ײ��ʡA�t�� * �ڸ�2
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
	if (blood > 0) {
		if (KB % 3 == 0 && KB != 0) {
			shape.setTexture(&texture_hurt);
			if (hitdirection != 0) {
				direction *= hitdirection;
				hitdirection = 0;
			}
		}
		else {
			if (canAttack || Timer_Attack >= 0.5) {    //0.5���]�������ʵe�һݮɶ�
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					actionState = Game::Action::jump;
				}
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
				//�ե��^�k, �icommand���ݫ�G
				//���ܰѦ��I
				if (d_change) {
					shape.setOrigin(shape.getOrigin().x - (weaponWidth - manWidth) * direction, characterSize.y);
					shape.move(direction * manWidth / 2, 0);
					d_change = 0;
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
	if (Timer_animation >= switchTime) {
		current.y = (current.y + 1) % 10;
		Timer_animation -= switchTime;
	}
	shape.setTextureRect(sf::IntRect(current.x + (direction == 1 ? 0 : sizeOfTexture.x), 676 * current.y + 100, sizeOfTexture.x * direction, sizeOfTexture.y));// 676��step
	return 0;
}
//�Ǫ�
int enemy::Update(float deltaTime, mainPlayer& plyerOne)
{
	Timer_animation += deltaTime;
	if (!canAttack) {
		Timer_Attack += deltaTime;
		if (Timer_Attack <= 0.5 && Timer_Attack > 0.4) {
			Attack(plyerOne);
		}
		if (Timer_Attack >= 0.8) {
			canAttack = 1;
			plyerOne.isHit = 0;
			if (plyerOne.KB % 3 == 0 && plyerOne.KB != 0) {
				plyerOne.KB = 0;
			}
		}
	}
	if (blood > 0) {
		Chasing_point = plyerOne.shape.getPosition();
		if (plyerOne.isJumping) {
			Chasing_point.y = plyerOne.landingPOS;
		}
		Chasing_point.x -= plyerOne.direction * plyerOne.manWidth / 2;

		//�ڤ]�����D�o�q���Ʀr�b�F���A�ϥ��N�O�״_�@�ǻ~�t
		if (direction * plyerOne.direction < 0) {
			Chasing_point.x += 30 * plyerOne.direction;
		}

		switchTime = 0.05;
		sf::Vector2i temp;
		//shape.setTexture(texture_idle);
		if (isHit || (Timer_Wait > 0 && Timer_Wait < 0.5)) {
			if (isHit) {
				shape.setTexture(texture_hurt_ptr);
				shape.move(-0.25 * direction, 0);
			}
			Timer_Wait += deltaTime;
		}
		else {
			Timer_Wait = 0;
			if (shape.getPosition().x - Chasing_point.x > 50) {
				if (direction != -1) {
					direction = -1;
					d_change = 1;
				}
				if (shape.getPosition().x - Chasing_point.x > weaponWidth) {
					shape.setTexture(texture_run_ptr);
					temp.x = -1;
				}
			}
			else if (shape.getPosition().x - Chasing_point.x <= -50) {
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
			if (d_change) {
				shape.setOrigin(shape.getOrigin().x - (weaponWidth - manWidth) * direction, characterSize.y);
				shape.move(direction * manWidth / 2, 0);
				d_change = 0;
			}
			if (fabs(Chasing_point.x - shape.getPosition().x) <= weaponWidth && canAttack && plyerOne.blood > 0) {
				canAttack = 0;
				switchTime = 0.05;
				Timer_Attack = 0;
				shape.setTexture(texture_attack_ptr);
				current.y = 18;
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
	shape.setTextureRect(sf::IntRect(current.x + (direction == 1 ? 0 : sizeOfTexture.x), 301 * current.y + 70, sizeOfTexture.x * direction, sizeOfTexture.y));
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

void mainPlayer::Attack(std::vector<enemy>&monsters)
{
	for (int i = 0; i < monsters.size(); ++i) {
		if (direction * monsters[i].direction < 0 && !monsters[i].isHit) {
			if (fabs(monsters[i].shape.getPosition().x - shape.getPosition().x) <= this -> weaponWidth - 10 
				&& fabs(monsters[i].shape.getPosition().y - shape.getPosition().y) <= 20) {
				monsters[i].blood -= 50;
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
		players.KB++;
		if (direction * players.direction < 0) {
			players.hitdirection = 1;
		}
		else {
			players.hitdirection = -1;
		}
		players.blood -= 50;
		players.isHit = 1;
		if (players.blood <= 0) {
			players.current.y = 0;
		}
	}
}