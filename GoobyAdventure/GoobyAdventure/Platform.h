#pragma once
#include "Renderable.h"

class Platform : public Renderable {
public:
	Platform(int, int, int, int); //x, y, width, height
	~Platform();

	sf::RectangleShape plat; //platforms are just shapes for now
	int x;
	int y;
	int width;
	int height;
};
