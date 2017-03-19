#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Renderable.h"

class Item : public Renderable {
public:
	Item();
	Item(int, std::string, int amount = 0);
	~Item();
	int getTier();
	std::string getName();
	std::string getDef();
	int getAmount();
	sf::Image image;
	sf::Texture texture;
	int amount;
private:
	int tier; // this will tell whether an item can be used or not in crafting
	std::string name;
	std::string def;

};