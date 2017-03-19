#include "Item.h"
#include "Manager.h"

Item::Item() {

}

Item::Item(int tier, std::string name, int amount) {
	this->name = name;
	this->tier = tier;
	this->amount = amount;
	image.loadFromFile("Assets/" + name + ".png");
	image.createMaskFromColor(sf::Color::Magenta);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale({ 0.5 + 50 / 40, 0.5 + 50 / 40 });
	if (name == "bullet") {
		this->def = "a plain bullet"; // needed for fire gun // T1
		sprite.setScale({ 50 / 14, 50 / 14 });
	}
	else if (name == "fire gun") { // makes the bullets shoot fire instead! // T2
		this->def = "you can shoot FIYAHHH";
		sprite.setScale({ 50 / 14, 50 / 14 });
	}
	else if (name == "red goo") { // required for the boots of leaping // T1
		this->def = "it looks springy";
	}
	else if (name == "boots of leaping") { // when these are made, get a +1 to jump height // T2
		this->def = "these boots aren't just made for walking";
	}
	else if (name == "green goo") { // this will be for armour // T1
		this->def = "it doesn't break???";
	}
	else if (name == "boots") { // these are required to make the boots of leaping // T1
		this->def = "plain boots";
	}
	else if (name == "armour") {
		this->def = "plain alien armour"; // for use in making different armours // T1
	}
	else if (name == "the bones of your enemies") {
		this->def = "morbid, but it works"; // stronger armour // T2
	}
	else if (name == "fashionable space suit") { // weaker armour, with higher jump //T2
		this->def = "it puts a spring in your step and a bullet in your heart";
	}
	else if (name == "extra boing bullets") { // these bullets bounce off walls //T2
		this->def = "hope it doesn't bounce on you too!!";
		sprite.setScale({ 50 / 14, 50 / 14 });
	}
	else if (name == "heavy boots") { // less jump, more armour //T2
		this->def = "i told you to go with the toe shoes, janet";
	}
}

Item::~Item() {}

int Item::getTier() { return this->tier; }
int Item::getAmount() { return this->amount; }
std::string Item::getName() { return this->name; }
std::string Item::getDef() { return this->def; }