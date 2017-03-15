#include "LevelManager.h"

LevelManager::LevelManager() {
	spawner = sf::seconds(0);
	currentLevel = 1; //we start the game on level 1
	generateLevel(currentLevel);

	/*
	//random platform example
	for (int i = 0; i < 20; i++) {
		platforms.push_back(new Platform(240 * i, rand() % 116 + 532, rand() % 110 + 50);
	}
	*/
}

LevelManager::~LevelManager() {

}

void LevelManager::update(sf::Time deltaTime) {

	/*-----spawn new enemies into the game-----*/
	spawner += deltaTime;
	if (spawner.asSeconds() > 4) { //every 4 seconds
		enemies.push_back(new Enemy(rand() % (3 * CENTER_SCREEN), 515)); //spawn a new enemy randomly on the screen
		spawner = sf::seconds(0);
	}

}

void LevelManager::generateLevel(int level) {
	if (level == 1) {
		//initial long stretch
		platforms.push_back(new Platform(0, 600, 2000));

		//stairs
		platforms.push_back(new Platform(2000, 565, 100));
		platforms.push_back(new Platform(2100, 530, 100));
		platforms.push_back(new Platform(2200, 495, 100));
		platforms.push_back(new Platform(2300, 460, 400));
		//air plats
		platforms.push_back(new Platform(2400, 400, 200));
		platforms.push_back(new Platform(2400, 270, 200));
		platforms.push_back(new Platform(2400, 130, 200));
		//back down
		platforms.push_back(new Platform(2700, 495, 100));
		platforms.push_back(new Platform(2800, 530, 100));
		platforms.push_back(new Platform(2900, 565, 100));
		platforms.push_back(new Platform(3000, 600, 500));
	}
}