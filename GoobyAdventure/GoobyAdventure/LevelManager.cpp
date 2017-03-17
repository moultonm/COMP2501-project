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
	//moving platform starts at (3800, 630, 200) and it moves up to (3800, -200, 200)
	if (currentLevel == 1) {
		Platform* movingPlat = platforms.back();
		float tempY = movingPlat->y;
		if (movingPlat->y <= -200) movingPlat->upwards = false;
		else if (movingPlat->y >= 630) movingPlat->upwards = true;
		if (movingPlat->upwards) {
			movingPlat->y -= 125 * deltaTime.asSeconds();
			//if (player->velocity.y <= 0) player->position.y -= 145 * deltaTime.asSeconds();
		}
		else {
			movingPlat->y += 125 * deltaTime.asSeconds();
		}
		//if player is on the moving plat, make sure he doesn't fall through
		if (player->position.x + 43 > movingPlat->x && player->position.x + 20 < movingPlat->x + movingPlat->width
			&& player->position.y + 90 <= tempY) {
			player->groundLevel = movingPlat->y - 90;
			player->position.y -= 125 * deltaTime.asSeconds();
		}
	}

	/*-----spawn new enemies into the game-----*/
	/*spawner += deltaTime;
	if (spawner.asSeconds() > 4) { //every 4 seconds
		enemies.push_back(new Enemy(rand() % (3 * CENTER_SCREEN), 515)); //spawn a new enemy randomly on the screen
		spawner = sf::seconds(0);
	}*/

}

bool LevelManager::screenLimit(float x) {
	if (currentLevel == 1) {
		if (x >= 3960) { //can't go past the right border of the world (x = 4000)
			return true;
		}
	}
	return false;
}

//stairs should always be pushed lowest to highest in order (sort by y coordinate)
void LevelManager::generateLevel(int level) {
	if (level == 1) {
		platforms.push_back(new Platform(0, 665, 2000)); //first long stretch
		platforms.push_back(new Platform(3000, 665, 1000)); //lower rightside long stretch
		platforms.push_back(new Platform(2000, 630, 100)); //lower stairs
		platforms.push_back(new Platform(2900, 630, 100));
		platforms.push_back(new Platform(2100, 595, 100));
		platforms.push_back(new Platform(2800, 595, 100));
		platforms.push_back(new Platform(2200, 560, 100));
		platforms.push_back(new Platform(2700, 560, 100));
		platforms.push_back(new Platform(575, 535, 200)); //early left plat
		platforms.push_back(new Platform(1200, 535, 200)); //early right plat
		platforms.push_back(new Platform(2300, 525, 400)); //middle landing
		platforms.push_back(new Platform(2400, 465, 200)); //air plat mid
		platforms.push_back(new Platform(850, 405, 200)); //early mid plat
		platforms.push_back(new Platform(2400, 335, 200)); //air plat mid
		platforms.push_back(new Platform(2400, 195, 200)); //air plat mid

		platforms.push_back(new Platform(3000, -200, 700)); //upper rightside stretch
		platforms.push_back(new Platform(2900, -235, 100)); //upper stairs
		platforms.push_back(new Platform(2800, -270, 100));
		platforms.push_back(new Platform(2700, -305, 100));
		platforms.push_back(new Platform(2300, -340, 400)); //upper middle landing
		platforms.push_back(new Platform(0, -340, 2300)); //upper exit

		//moving platform starts at (3800, 630, 200) and it moves up to (3800, -200, 200)
		platforms.push_back(new Platform(3800, 630, 200));

		loot.push_back(new Loot(2470, 135)); //loot on top platform
		loot.push_back(new Loot(3300, 605)); //loot on ground
		loot.push_back(new Loot(3200, -260)); //upper loot

		//ENEMIES
		enemies.push_back(new Enemy(400, 570));
		enemies.push_back(new Enemy(800, 570));
		enemies.push_back(new Enemy(1200, 570));
		enemies.push_back(new Enemy(1800, 570));
		enemies.push_back(new Enemy(3000, 570));
		enemies.push_back(new Enemy(3400, 570));
		enemies.push_back(new Enemy(3800, 570));
		//upper
		enemies.push_back(new Enemy(400, -435));
		enemies.push_back(new Enemy(1200, -435));
		enemies.push_back(new Enemy(1600, -435));
		enemies.push_back(new Enemy(2000, -435));
	}
}