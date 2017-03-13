#include "Platform.h"

Platform::Platform(int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	width = w;
	height = h;
	plat.setSize(sf::Vector2f(w, h));
	plat.setPosition(sf::Vector2f(x, y));
	plat.setFillColor(sf::Color::Blue);
}

Platform::~Platform() {

}