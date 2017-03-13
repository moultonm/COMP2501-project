#pragma once
#include <SFML/Graphics.hpp>
#include "defs.h"

class LevelScreen {
public:
	LevelScreen();
	~LevelScreen();
	void render(sf::RenderWindow*);
	int index;

private:
	sf::Font font;
	sf::Text level1, crafting, levelscreen; // font for the rectangles, levelscreen is title
	sf::RectangleShape rect1, rectC; // rect for level 1, rect for crafting
	sf::RectangleShape selector; // magenta selector rectangle eh
};