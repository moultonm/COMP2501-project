#include "Model.h"

Model::Model() {

}

Model::~Model() {

}

void Model::update(sf::Time deltaTime) {
	if (*gameState == TITLE) {
		return; //don't update anything if we haven't started the game yet
	}

	for (int i = 0; i < updateables.size(); i++) {
		updateables[i]->update(deltaTime);
	}
}
