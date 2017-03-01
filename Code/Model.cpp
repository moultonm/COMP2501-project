#include "Model.h"

Model::Model() {
	spawner = sf::seconds(0);
}

Model::~Model() {

}

void Model::update(sf::Time deltaTime) {
	if (*gameState == TITLE) {
		return; //don't update anything if we haven't started the game yet
	}

	/*-----spawn new enemies into the game-----*/
	spawner += deltaTime;
	if (spawner.asSeconds() > 5) { //every 5 seconds
		enemies.push_back(new Enemy(rand() % (2 * CENTER))); //spawn a new enemy randomly on the screen
		spawner = sf::seconds(0);
	}

	/*-----updateables-----*/
	for (int i = 0; i < updateables.size(); i++) {
		updateables[i]->update(deltaTime);
	}

	/*-----update enemies-----*/
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update(deltaTime);
	}
}
