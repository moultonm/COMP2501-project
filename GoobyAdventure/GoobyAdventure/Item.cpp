#include "Item.h"
#include "Manager.h"

Item::Item() {

}

Item::Item(int tier, std::string name) {
	this->name = name;
	this->tier = tier;
	image.loadFromFile("Assets/" + name + ".png");
	image.createMaskFromColor(sf::Color::Magenta);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	if (name == "bullet") {
		this->def = "a plain bullet";
		this->sprite.setTexture(texture)
			;
	}
	else if (name == "flux capacitor") {
		this->def = "it's fluxing and firy!";
	}
	else if (name == "fire gun") {
		this->def = "you can shoot FIYAHHH";
	}
}

Item::~Item() {}

int Item::getTier() { return this->tier; }
int Item::getAmount() { return this->amount; }
std::string Item::getName() { return this->name; }
std::string Item::getDef() { return this->def; }