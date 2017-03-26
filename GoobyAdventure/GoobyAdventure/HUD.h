#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "defs.h"
#include <iostream>
#include <sstream>
#include <string>

class HUD : public Renderable {
public:
	HUD();
	~HUD();
	void render(sf::RenderWindow*);
	void update(int); // takes in points

	sf::Sprite armour;
	sf::Image armourIm;
	sf::Texture armourTex;
	sf::Font font;
	sf::Text points;
	std::stringstream ss;
};