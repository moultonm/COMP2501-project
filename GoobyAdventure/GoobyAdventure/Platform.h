#pragma once
#include "Renderable.h"
#include <SFML/Graphics.hpp>

class Platform : public Renderable {
public:
	Platform(int, int, int); //x, y, width
	~Platform();

	sf::VertexArray plat; //platforms are just shapes for now
	sf::Texture* texture;
	int x;
	int y;
	int width;
	int height;
};
