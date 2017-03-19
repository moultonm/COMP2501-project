#include "Control.h"

Control::Control(Model* m, View* v) {
	model = m;
	view = v;
	counter = 0;
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
		case sf::Event::KeyPressed:
			if (*gameState == TITLE) {
				if (event.key.code == sf::Keyboard::Space) {
					*gameState = LEVEL; //start game if we press space on the title screen
				}
			}
			else if (*gameState == LEVEL) {
				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S) {
					model->levelScreen->index++;
					model->levelScreen->index %= 3; //index can be 0, 1, 2
				}
				else if (event.key.code == sf::Keyboard::Return) {
					if (model->levelScreen->index == 0) {
						*gameState = GAME;
						model->levelManager.currentLevel = 1;
						model->levelManager.generateLevel();
						view->text.setCharacterSize(16);
						view->text.setPosition(25, 25);
					}
					else if (model->levelScreen->index == 1) {
						*gameState = GAME;
						model->levelManager.currentLevel = 2;
						model->levelManager.generateLevel();
						view->text.setCharacterSize(16);
						view->text.setPosition(25, 25);
					}
					else {
						*gameState = CRAFT;
					}
				}

			}
			break;
		case sf::Event::KeyReleased:
			//SO: buckle in because here's why we're using key release here instead of something else.
			// 1) it happens once so it's more precise than just using key pressed
			// 2) we're polling for events here so we're gonna try using keyPressed in the future but for now? nah
			if (event.key.code == sf::Keyboard::Escape) {// get out of here to the level screen
				*gameState = LEVEL;
			}
			if (*gameState == CRAFT) {
				if (model->crafting->select1 == 0 || model->crafting->select2 == 0) {
					//still picking ingredients
					if (event.key.code == sf::Keyboard::W) {
						// move up list
						if (model->crafting->index - 1 >= 0) {
							model->crafting->index--;
						}
						else {
							model->crafting->index = model->crafting->itemToSel.size() - 1;// loop to bottom
						}
					}
					if (event.key.code == sf::Keyboard::S) {
						// move down list
						if (model->crafting->index + 1 < model->crafting->itemToSel.size()) {
							model->crafting->index++;

						}
						else {
							model->crafting->index = 0;// loop to top
						}
					}

				}
				if (event.key.code == sf::Keyboard::Return) {
					//the making selections section
					if (model->crafting->select1 == 0) { // pick the first ingredient!
						model->crafting->select1 = model->items[model->crafting->index];
						model->crafting->itemDesc.setString(model->items[model->crafting->index]->getDef());
						if (model->crafting->toMake != 0) {
							model->crafting->toMake = 0;
							model->crafting->craftDesc.setString("");
							model->crafting->craftName.setString("");
						}
						model->crafting->boxSelector.setPosition(495, 120);

					}
					else if (model->crafting->select1 != 0 && model->crafting->select2 == 0) { // pick the second ingredient
						model->crafting->select2 = model->items[model->crafting->index];
						model->crafting->itemDesc.setString(model->items[model->crafting->index]->getDef());
						model->crafting->boxSelector.setPosition(520, 370);
					}
					else { //CRAFTTTTTT
						model->crafting->craft(model->items, model->player);
						model->crafting->boxSelector.setPosition(395, 120);
					}
				}
			}
			else {
				break;
			}
			break;
		}
		//Spacebar to fire bullets
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
			if (*gameState == GAME) model->player->fireBullet();
		}
	}

	if (*gameState != GAME) {
		return; //leave the inputs call if the game hasn't started yet
	}

	//reset velocity if no inputs are given
	model->player->velocity.x = 0;
	model->player->isMoving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		model->player->velocity.x = -model->player->speed;
		model->player->facing = 2;
		model->player->isMoving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		model->player->velocity.x = +model->player->speed;
		model->player->facing = 0;
		model->player->isMoving = true;
	}



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (!model->player->isJumping) { //if hes not already jumping
			model->player->isJumping = true; //set him to jumping
			model->player->velocity.y = -model->player->jumpSpeed; //and velocity up!
			model->player->jumpLocation = model->player->groundLevel; //store height we jumped from so we know how high to go
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		//model->player->velocity.y = +model->player->speed;
		//moving up/down might be relevant later.. ladders? floating in space?!
	}
}