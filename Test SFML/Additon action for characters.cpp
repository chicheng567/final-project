#include "Game.h"
#include "characters.h"
#include<cmath>
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
			if (fabs(monsters[0].shape.getPosition().x - shape.getPosition().x) <= weaponWidth) {
				monsters[i].blood -= 50;
				std::cout << monsters[0].blood << "\n";
				monsters[i].isHit = 1;
				if (monsters[0].blood <= 0) {
					monsters[0].current.y = 0;
				}
			}
		}
	}
}