#include "characters.h"
characters::characters(std::string path, sf::Vector2f size) : totalTime(0), switchTime(0.3f)
{
	if (Texture.loadFromFile(path)) {
		std::cout << "correct";
	}
	shape.setSize(size);
	Texture.setSmooth(1);
	shape.setTexture(&Texture);
}

mainPlayer::mainPlayer(std::string path, sf::Vector2f size) : characters(path, size)
{
	current = { 0, 0 };
	shape.setPosition(500, 500);
	sizeOfTexture = Texture.getSize();
	sizeOfTexture.x /= 3;
	sizeOfTexture.y /= 9;
}

void mainPlayer::Update(float deltaTime)
{
	totalTime += deltaTime;
	current.y = 0;
	switchTime = 0.3;
	int direction = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		shape.move(0, -1.5);
		current.y = 1;
		switchTime = 0.05;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		shape.move(-1.5, 0);
		direction = -1;
		current.y = 1;
		switchTime = 0.05;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		shape.move(0, 1.5);
		current.y = 1;
		switchTime = 0.05;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		shape.move(1.5, 0);
		current.y = 1;
		switchTime = 0.05;
	}
	if (totalTime >= switchTime) {
		current.x = (current.x + 1) % 3;
		totalTime = 0;
	}
	shape.setTextureRect(sf::IntRect(sizeOfTexture.x * current.x, sizeOfTexture.y * current.y, sizeOfTexture.x * direction, sizeOfTexture.y)); //°_©lÂI¡A½d³ò
}
