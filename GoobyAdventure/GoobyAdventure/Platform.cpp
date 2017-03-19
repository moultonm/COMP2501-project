#include "Platform.h"

Platform::Platform(int x, int y, int w) {
	this->x = x;
	this->y = y;
	width = w;
	height = 35;
	upwards = true;
	plat.setPrimitiveType(sf::Quads);
	plat.resize(4);
	plat[0].position = sf::Vector2f(x, y);
	plat[1].position = sf::Vector2f(x + width, y);
	plat[2].position = sf::Vector2f(x + width, y + 35);
	plat[3].position = sf::Vector2f(x, y + 35);
	plat[0].texCoords = sf::Vector2f(0, 0);
	plat[1].texCoords = sf::Vector2f(69, 0);
	plat[2].texCoords = sf::Vector2f(69, 35);
	plat[3].texCoords = sf::Vector2f(0, 35);
}

Platform::~Platform() {

}