#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Renderable.h"

/* ITEMS:
Tier 1: these items are used for crafting/creating upgrades
bullet
flux capacitor

*/

/* COMBOS:
bullet + flux capacitor = fire shooter

*/

class Item : public Renderable {
public:
	Item();
	Item(int, std::string);
	~Item();
	int getTier();
	std::string getName();
	std::string getDef();
	int getAmount();
	sf::Image image;
	sf::Texture texture;
private:
	int tier; // this will tell whether an item can be used or not in crafting
	int amount;
	std::string name;
	std::string def;

};