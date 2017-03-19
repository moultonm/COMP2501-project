#include "LevelManager.h"

LevelManager::LevelManager() {
	spawner = sf::seconds(0);
	currentLevel = 1; //we start the game on level 1

	exit.setSize(sf::Vector2f(75, 50));
	exit.setFillColor(sf::Color::Blue);
}

LevelManager::~LevelManager() {

}

void LevelManager::update(sf::Time deltaTime) {
	exit.setPosition(exitx, exity);
	//moving platform starts at (3800, 630, 200) and it moves up to (3800, -250, 200)
	if (currentLevel == 1) {
		Platform* movingPlat = platforms.back();
		float tempY = movingPlat->y;
		if (movingPlat->y <= -250) movingPlat->upwards = false;
		else if (movingPlat->y >= 630) movingPlat->upwards = true;
		if (movingPlat->upwards) {
			movingPlat->y -= 125 * deltaTime.asSeconds();
		}
		else {
			movingPlat->y += 125 * deltaTime.asSeconds();
		}
		//if player is on the moving plat, make sure he doesn't fall through
		if (player->position.x + 43 > movingPlat->x && player->position.x + 20 < movingPlat->x + movingPlat->width
			&& player->position.y + 90 <= tempY) {
			player->groundLevel = movingPlat->y - 90;
			player->position.y -= 125 * deltaTime.asSeconds();
			player->movePlat = true;
		}
		else { player->movePlat = false; }
	}
	else if (currentLevel == 2) { //SECOND LEVEL UPDATE CODE
		//moving platform starts at (3900, 175, 200) and it moves up to (4400, 175, 200)
		Platform* movingPlat = platforms.back();
		float tempX = movingPlat->x;
		if (movingPlat->x <= 3900) movingPlat->upwards = false;
		else if (movingPlat->x >= 4400) movingPlat->upwards = true;
		if (movingPlat->upwards) {
			movingPlat->x -= 125 * deltaTime.asSeconds();
		}
		else {
			movingPlat->x += 125 * deltaTime.asSeconds();
		}
		//if player is on the moving plat, make sure he doesn't fall through
		if (player->position.x + 43 > tempX && player->position.x + 20 < tempX + movingPlat->width
			&& player->position.y + 90 <= movingPlat->y) {
			if (movingPlat->upwards) { player->position.x -= 125 * deltaTime.asSeconds(); }
			else { player->position.x += 125 * deltaTime.asSeconds(); }
		}
	}
}

bool LevelManager::screenLimit(float x) {
	if (currentLevel == 1) {
		if (x >= 3960) { //can't go past the right border of the world (x = 4000)
			return true;
		}
	}

	if (currentLevel == 2) {
		if (x >= 4960) { //can't go past the right border of the world (x = 5000)
			return true;
		}
	}
	return false;
}

//stairs should always be pushed lowest to highest in order (sort by y coordinate)
void LevelManager::generateLevel() {
	platforms.clear();
	loot.clear();
	enemies.clear();

	if (currentLevel == 1) {
		player->groundLevel = 600;
		player->position.x = 15;
		player->position.y = player->groundLevel - 50;

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

		//moving platform starts at (3800, 630, 200) and it moves up to (3800, -250, 200)
		platforms.push_back(new Platform(3800, 630, 200));

		loot.push_back(new Loot(2470, 135)); //loot on top platform
		loot.push_back(new Loot(3300, 605)); //loot on ground
		loot.push_back(new Loot(3200, -260)); //upper loot
		loot.push_back(new Loot(1200, -400));
		exitx = 100;
		exity = -390;
		exit.setPosition(exitx, exity);

		//ENEMIES
		enemies.push_back(new Enemy(400, 565));
		enemies.push_back(new Enemy(800, 565));
		enemies.push_back(new Enemy(1200, 565));
		enemies.push_back(new Enemy(1800, 565));
		enemies.push_back(new Enemy(3200, 565));
		enemies.push_back(new Enemy(3500, 565));
		enemies.push_back(new Enemy(3800, 565));
		//mid plats
		enemies.push_back(new Enemy(2400, 315));
		enemies.push_back(new Enemy(2450, 80));
		//upper
		enemies.push_back(new Enemy(400, -430));
		enemies.push_back(new Enemy(1200, -430));
		enemies.push_back(new Enemy(1600, -430));
		enemies.push_back(new Enemy(2000, -430));
	}
	else if (currentLevel == 2) {
		player->groundLevel = 600;
		player->position.x = 15;
		player->position.y = player->groundLevel - 50;

		platforms.push_back(new Platform(0, 665, 1000)); //first long stretch
		platforms.push_back(new Platform(1000, 630, 100)); //lower stairs
		platforms.push_back(new Platform(1100, 595, 100));
		platforms.push_back(new Platform(1200, 560, 100));
		platforms.push_back(new Platform(1300, 525, 400)); //first landing
		platforms.push_back(new Platform(1700, 490, 100));
		platforms.push_back(new Platform(1800, 455, 100));
		platforms.push_back(new Platform(1900, 420, 100));
		platforms.push_back(new Platform(2000, 385, 600)); //second landing
		platforms.push_back(new Platform(2600, 350, 100));
		platforms.push_back(new Platform(2700, 315, 100));
		platforms.push_back(new Platform(2800, 280, 100));
		platforms.push_back(new Platform(2900, 245, 100));
		platforms.push_back(new Platform(3000, 210, 100));
		platforms.push_back(new Platform(3100, 175, 800)); //landing before moving plat
		platforms.push_back(new Platform(4600, 175, 400)); //exit after moving plat

		//moving platform starts at (3900, 175, 200) and it moves up to (4400, 175, 200)
		platforms.push_back(new Platform(4000, 175, 200));

		exitx = 4850;
		exity = 125;
		exit.setPosition(exitx, exity);

		//ENEMIES
		enemies.push_back(new Enemy(600, 565));
		enemies.push_back(new Enemy(1400, 450));
		enemies.push_back(new Enemy(2400, 300));
		enemies.push_back(new Enemy(3200, 80));
		enemies.push_back(new Enemy(4800, 80));

		//LOOT
		loot.push_back(new Loot(800, 605)); //loot 1
		loot.push_back(new Loot(2100, 325)); //loot 2
		loot.push_back(new Loot(4100, 115)); //loot 3
	}
}