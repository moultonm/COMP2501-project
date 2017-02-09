#include "View.h"

View::View(Model* m) {
	model = m;

	width = 800;
	height = 600;

	//initialize our window
	window.create(sf::VideoMode(width, height), "COMP2501-Gooby_Space_Adventure");
	window.setFramerateLimit(45);

	//initializes title text for now
	font.loadFromFile("Assets/arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Green);
	text.setCharacterSize(28);
	text.setPosition(width / 4, height / 4);
	text.setString("Gooby's Space Adventure\n\n        (Press Space)");
}

View::~View() {

}

void View::render() {
	window.clear(sf::Color::Black);

	if (*gameState == TITLE) {
		window.draw(text);
		window.display();
		return; //draw title screen, then exit the render call
	}

	for (int i = 0; i < renderables.size(); i++) {
		window.draw(renderables[i]->sprite);
	}

	window.display();
}
