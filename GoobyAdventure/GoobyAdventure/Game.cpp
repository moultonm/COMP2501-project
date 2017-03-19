#include "Game.h"

/*
Project: COMP2501A - Final Project - Gooby's Space Adventure
Authors: Alexandra Wilson (100998162), Matthew Moulton (101010631)
*/
//Press ESC at any time to go back to the Level Select screen
// Enter chooses selected menu item
// W&S navigate menus
// A&D move left and right
// W jumps
// space shoots

Game::Game() {
	model = new Model();
	view = new View(model);
	control = new Control(model, view);

	model->updateables.push_back(model->player);
	view->renderables.push_back(model->player);

	gameState = TITLE;
	control->gameState = &gameState;
	model->gameState = &gameState;
	view->gameState = &gameState;
}

Game::~Game() {

}

void Game::loop() {
	sf::Time deltaTime;

	while (view->window.isOpen()) {
		deltaTime = clock.restart();

		control->inputs();
		model->update(deltaTime);
		view->render();
	}

	view->window.close();
}