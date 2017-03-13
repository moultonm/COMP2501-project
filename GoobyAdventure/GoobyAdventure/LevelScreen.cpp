#include "LevelScreen.h"

LevelScreen::LevelScreen() : index(0) {
	// load a font
	font.loadFromFile("Assets/arial.ttf");

	// set up the text at the top
	levelscreen.setFont(font);
	levelscreen.setString("LEVEL SELECTION SCREEN");
	levelscreen.setCharacterSize(50);
	levelscreen.setFillColor(sf::Color::Black);
	levelscreen.setPosition(sf::Vector2f(200, 50));

	level1.setFont(font);
	level1.setString("LEVEL ONE");
	level1.setCharacterSize(20);
	level1.setFillColor(sf::Color::Black);
	level1.setPosition(sf::Vector2f(425, 150));

	crafting.setFont(font);
	crafting.setString("CRAFTING");
	crafting.setCharacterSize(20);
	crafting.setFillColor(sf::Color::Black);
	crafting.setPosition(sf::Vector2f(425, 275));

	rect1.setPosition(sf::Vector2f(400, 125));
	rect1.setSize(sf::Vector2f(200, 100));
	rect1.setOutlineThickness(5);
	rect1.setOutlineColor(sf::Color(100, 100, 100));
	rect1.setFillColor(sf::Color::White);

	rectC.setPosition(sf::Vector2f(400, 250));
	rectC.setSize(sf::Vector2f(200, 100));
	rectC.setOutlineThickness(5);
	rectC.setOutlineColor(sf::Color(100, 100, 100));
	rectC.setFillColor(sf::Color::White);

	selector.setPosition(sf::Vector2f(395, 120));
	selector.setSize(sf::Vector2f(210, 110));
	selector.setOutlineColor(sf::Color::Magenta);
	selector.setOutlineThickness(2);
	selector.setFillColor(sf::Color::White);
}

LevelScreen::~LevelScreen() {};

void LevelScreen::render(sf::RenderWindow* window) {
	selector.setPosition(395, 120 + index * 125);

	window->clear(sf::Color::White);

	window->draw(selector);
	window->draw(rect1);
	window->draw(rectC);
	window->draw(level1);
	window->draw(crafting);
	window->draw(levelscreen);

}