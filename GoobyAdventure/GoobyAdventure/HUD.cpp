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
	points.setCharacterSize(24);
	points.setFillColor(sf::Color::Magenta);
	points.setPosition(50, 10);
	points.setString("2");
}
HUD::~HUD() {}

void HUD::render(sf::RenderWindow* window) {
	window->draw(armour);
	window->draw(points);
}

void HUD::update(int points) {
	ss.str(std::string());
	ss >> points;
	this->points.setString(ss.str());
}