#include "Control.h"

Control::Control(Model* m, View* v) {
	model = m;
	view = v;
}

Control::~Control() {

}

void Control::inputs() {
	sf::Event event;

	while (view->window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			this->view->window.close();
			break;
		}
	}

	if (*gameState == TITLE) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			*gameState = GAME; //start game if we press space on the title screen
		}
		return; //leave the inputs call if the game hasn't started yet
	}

	//reset velocity if no inputs are given
	model->player->velocity.x = 0;
	model->player->velocity.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		model->player->velocity.x = -model->player->speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		model->player->velocity.x = +model->player->speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		model->player->velocity.y = -model->player->speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		model->player->velocity.y = +model->player->speed;
	}
}
