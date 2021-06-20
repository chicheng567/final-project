#include "Game.h"
#include "characters.h"
#include <stdlib.h>
#include <time.h>
Game::Map::Map() :wave(0)
{
	monster3 = { 3, 3, 2, 0 };
	monster9 = { 0, 2, 3, 0 };
	monster1 = { 0, 0, 0, 6 };
}

int Game::Map::wave_detect(int monsterNUM)
{
	static int last = 0;
	if (last && monsterNUM == 0) {
		return 1;
	}
	else {
		last = monsterNUM;
		return 0;
	}
}

void Game::sponse_monster()
{
	if (map.wave < 4) {
		srand(time(NULL));
		sf::Vector2f sponse_POS;
		for (int i = 0; i < map.monster3[map.wave]; ++i) {
			sponse_POS.x = rand() % 2 * range.width + range.left;
			sponse_POS.y = ((float)rand() / RAND_MAX) * range.height + range.top;
			enemy new_enemy(sf::Vector2f(200/1.8, 215/1.8), 0);
			new_enemy.shape.setPosition(sponse_POS);
			monsters.push_back(new_enemy);
		}
		for (int i = 0; i < map.monster9[map.wave]; ++i) {
			sponse_POS.x = rand() % 2 * range.width + range.left;
			sponse_POS.y = (rand() % 4) * (range.height / 4) + range.top;
			enemy new_enemy(sf::Vector2f(200 / 1.8, 215 / 1.8), 1);
			new_enemy.shape.setPosition(sponse_POS);
			monsters.push_back(new_enemy);
		}
		for (int i = 0; i < map.monster1[map.wave]; ++i) {
			sponse_POS.x = rand() % 2 * range.width + range.left;
			sponse_POS.y = ((float)rand() / RAND_MAX) * range.height + range.top;
			enemy new_enemy(sf::Vector2f(200 / 1.8, 215 / 1.8), 2);
			new_enemy.shape.setPosition(sponse_POS);
			monsters.push_back(new_enemy);
		}
	}
	else if (map.wave == 4) {
		boss Boss;
		Boss.shape.setPosition(range.left + range.width * 3 / 5, range.top + range.height/2);
		boss_vec.push_back(Boss);
	}
	map.wave++;
}