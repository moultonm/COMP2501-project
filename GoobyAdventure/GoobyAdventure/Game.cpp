#include "Game.h"

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