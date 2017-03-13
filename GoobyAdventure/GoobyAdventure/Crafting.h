#pragma once
#include <SFML/Graphics.hpp>
#include "defs.h"
#include "Item.h"
#include <string>
#include <iostream>
#include <vector>

class Crafting {
public:
	Crafting();
	~Crafting();
	void render(sf::RenderWindow*);
	void craft(std::vector<Item*>&);
	void menu(std::vector<Item*>&);
	Item* select1;
	Item* select2;
	Item* toMake;
	int index;
	sf::Font font;
	sf::Text top;
	sf::Text itemDesc;
	sf::Text craftName;
	sf::Text craftDesc;
	std::vector<sf::Text> itemToSel;
	sf::RectangleShape left, craftingLarge, smallLeft, smallRight, smallCraft, craftNameBox, craftDescBox, itemDescBox, itemSelector, boxSelector;
private:


};