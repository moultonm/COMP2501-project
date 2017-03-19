#include "HUD.h"

HUD::HUD() {
	ss.str(std::string());
	armourIm.loadFromFile("Assets/armour.png");
	armourIm.createMaskFromColor(sf::Color::Magenta);
	armourTex.loadFromImage(armourIm);
	armour.setTexture(armourTex);
	armour.setPosition(10, 10);
	font.loadFromFile("Assets/Escalope_Crust-One.ttf");
	points.setFont(font);
	points.setCharacterSize(30);
	points.setFillColor(sf::Color::White);
	points.setPosition(CENTER_SCREEN - 30, 10);
	points.setString("0");
}
HUD::~HUD() {}

void HUD::render(sf::RenderWindow* window) {
	window->draw(armour);
}

void HUD::update(int points) {
	ss.str(std::string());
	ss >> points;
	this->points.setString(ss.str());
}