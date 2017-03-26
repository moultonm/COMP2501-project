#include "Model.h"

Model::Model() {
	player = new Player();
	score = 0;
	crafting = new Crafting();
	levelScreen = new LevelScreen();
	items.reserve(5);
	items.push_back(new Item(1, "bullet", 3));
	items.push_back(new Item(1, "red goo", 5));
	items.push_back(new Item(1, "boots", 4));
	levelManager.player = player;
}

Model::~Model() {

}

//many of these loops can be combined, but that can be optimized later
void Model::update(sf::Time deltaTime) {
	if (*gameState != GAME) {
		return; //don't update anything if we haven't started the game yet
	}

	/*-----check if platform is blocking player-----*/
	for (int i = 0; i < levelManager.platforms.size(); i++) {
		//stop moving right if there is a plat in the way
		if (player->velocity.x > 0 && player->position.x + 43 >= levelManager.platforms[i]->x && player->position.x + 38 < levelManager.platforms[i]->x
			&& levelManager.platforms[i]->y > player->position.y + 10 && levelManager.platforms[i]->y < player->position.y + 90) {
			player->velocity.x = 0;
		}//stop moving left if there is a plat in the way
		if (player->velocity.x < 0 && player->position.x + 25 >= levelManager.platforms[i]->x + levelManager.platforms[i]->width && player->position.x + 20 < levelManager.platforms[i]->x + levelManager.platforms[i]->width
			&& levelManager.platforms[i]->y > player->position.y + 10 && levelManager.platforms[i]->y < player->position.y + 90) {
			player->velocity.x = 0;
		}
	}

	/*-----check if platform is blocking enemies-----*/
	for (int i = 0; i < levelManager.platforms.size(); i++) {
		for (int j = 0; j < levelManager.enemies.size(); j++) {
			//stop moving right if there is a plat in the way
			if (levelManager.enemies[j]->velocity.x > 0 && levelManager.enemies[j]->position.x + 73 >= levelManager.platforms[i]->x && levelManager.enemies[j]->position.x + 10 < levelManager.platforms[i]->x
				&& levelManager.platforms[i]->y > levelManager.enemies[j]->position.y + 10 && levelManager.platforms[i]->y < levelManager.enemies[j]->position.y + 90) {
				levelManager.enemies[j]->velocity.x *= -1;
			}//stop moving left if there is a plat in the way
			if (levelManager.enemies[j]->velocity.x < 0 && levelManager.enemies[j]->position.x + 20 >= levelManager.platforms[i]->x + levelManager.platforms[i]->width && levelManager.enemies[j]->position.x + 15 < levelManager.platforms[i]->x + levelManager.platforms[i]->width
				&& levelManager.platforms[i]->y > levelManager.enemies[j]->position.y + 10 && levelManager.platforms[i]->y < levelManager.enemies[j]->position.y + 90) {
				levelManager.enemies[j]->velocity.x *= -1;
			}
		}
	}

	/*-----check if player hits right edge of world-----*/
	if (levelManager.screenLimit(player->position.x)) { //do we care to un-center the player at this point too? fix the camera like leftside..
		player->velocity.x = -player->speed;
	}

	/*-----level manager can spawn enemies, move platforms etc.-----*/
	levelManager.update(deltaTime);

	/*-----updateables-----*/
	for (int i = 0; i < updateables.size(); i++) {
		updateables[i]->update(deltaTime);
	}

	/*-----check if player is on a platform-----*/
	bool gotOne = false;
	for (int i = 0; i < levelManager.platforms.size(); i++) {
		if (player->position.x + 43 > levelManager.platforms[i]->x && player->position.x + 20 < levelManager.platforms[i]->x + levelManager.platforms[i]->width
			&& player->position.y + 90 <= levelManager.platforms[i]->y) { //have to mess with the player's coordinates since the sprite is crappy
			player->groundLevel = levelManager.platforms[i]->y - 90; //set groundlevel to the platform we are on (-90 is to match the sprites feet instead of his top box)
			gotOne = true;
		}
		else if (!gotOne) {//!(player->position.x + 40 > levelManager.platforms[i]->x && player->position.x + 25 < levelManager.platforms[i]->x + levelManager.platforms[i]->width)) { //reset groundlevel if we aren't on a platform
			player->groundLevel = 600; //this value is the "floor" level, can be updated for each level once levels are designed
		}
	}

	/*-----check if enemy is on a platform-----*/
	for (int i = 0; i < levelManager.platforms.size(); i++) {
		for (int j = 0; j < levelManager.enemies.size(); j++) {
			if (levelManager.enemies[j]->position.x + 73 > levelManager.platforms[i]->x && levelManager.enemies[j]->position.x + 10 < levelManager.platforms[i]->x + levelManager.platforms[i]->width
				&& levelManager.enemies[j]->position.y + 80 <= levelManager.platforms[i]->y) {
				levelManager.enemies[j]->groundLevel = levelManager.platforms[i]->y - 80;
			}
		}
	}

	/*-----update enemies-----*/
	for (int i = 0; i < levelManager.enemies.size(); i++) {
		if (levelManager.screenLimit(levelManager.enemies[i]->position.x)) { //make sure enemy doesn't leave rightside of screen
			levelManager.enemies[i]->velocity.x = -levelManager.enemies[i]->speed;
		}
		levelManager.enemies[i]->update(deltaTime, player);
		/*-----attempt to kill enemy by jumping on him-----*/
		if (player->isJumping && player->position.y + 22 > levelManager.enemies[i]->position.y - 65 && player->position.y + 22 < levelManager.enemies[i]->position.y + 15 &&
			player->position.x + 35 > levelManager.enemies[i]->position.x + 10 && player->position.x + 35 < levelManager.enemies[i]->position.x + 94) { //temporary magic numbers are to tighten the hitbox since the sprites aren't boxed well
			levelManager.enemies.erase(levelManager.enemies.begin() + i); //remove this enemy from the game
			score += 50;
		}
	}

	//DESPAWN BULLETS
	for (int i = 0; i < player->bullets.size(); i++) {
		if (player->bullets[i]->timeToLive < 0) {
			player->bullets.erase(player->bullets.begin() + i);
		}
	} //and enemy bullets
	for (int i = 0; i < levelManager.enemies.size(); i++) {
		for (int j = 0; j < levelManager.enemies[i]->bullets.size(); j++) {
			if (levelManager.enemies[i]->bullets[j]->timeToLive < 0) levelManager.enemies[i]->bullets.erase(levelManager.enemies[i]->bullets.begin() + j);
		}
	}

	//DESPAWN LOOTED LOOT
	for (int i = 0; i < levelManager.loot.size(); i++) {
		if (levelManager.loot[i]->looted) {
			levelManager.loot.erase(levelManager.loot.begin() + i);
		}
	}

	//UPDATE BULLETS
	for (int i = 0; i < player->bullets.size(); i++) {
		player->bullets[i]->update(deltaTime);
	} //and enemy bullets
	for (int i = 0; i < levelManager.enemies.size(); i++) {
		for (int j = 0; j < levelManager.enemies[i]->bullets.size(); j++) {
			levelManager.enemies[i]->bullets[j]->update(deltaTime);
		}
	}

	//CHECK COLLISION WITH BULLETSxENEMIES
	for (int i = 0; i < player->bullets.size(); i++) {
		for (int j = 0; j < levelManager.enemies.size(); j++) {
			if (pow((player->bullets[i]->position.x + 32) - (levelManager.enemies[j]->position.x + 52), 2) +
				pow((player->bullets[i]->position.y + 32) - (levelManager.enemies[j]->position.y + 54), 2) <=
				pow(32 + 26, 2)) {
				player->bullets.erase(player->bullets.begin() + i);
				levelManager.enemies.erase(levelManager.enemies.begin() + j);
				score += 50;
				break;
			}
		}
	}

	//CHECK COLLISION WITH LOOTxPLAYER
	for (int j = 0; j < levelManager.loot.size(); j++) {
		if (pow((player->position.x + 40) - (levelManager.loot[j]->x + 32), 2) +
			pow((player->position.y + 61) - (levelManager.loot[j]->y + 32), 2) <=
			pow(25 + 32, 2)) {
			if (!levelManager.loot[j]->looted) player->coins += levelManager.loot[j]->value;
			levelManager.loot[j]->looted = true;
			break;
		}
	}

	//CHECK COLLISION WITH PLAYERxENEMIES BULLETS
	for (int j = 0; j < levelManager.enemies.size(); j++) {
		for (int i = 0; i < levelManager.enemies[j]->bullets.size(); i++) {
			if (pow((player->position.x + 40) - (levelManager.enemies[j]->bullets[i]->position.x + 32), 2) +
				pow((player->position.y + 61) - (levelManager.enemies[j]->bullets[i]->position.y + 32), 2) <=
				pow(25 + 32, 2)) {
				if (player->armour > 0) player->armour--;
				else *gameState = GAMEOVER; //game over
				levelManager.enemies[j]->bullets.erase(levelManager.enemies[j]->bullets.begin() + i);
				break;
			}
		}
	}

	//CHECK IF WE REACHED THE EXIT
	if (player->position.x + 40 > levelManager.exitx && player->position.x + 20 < levelManager.exitx + 75 && player->position.y < levelManager.exity + 140 && player->position.y > levelManager.exity - 95) {
		if (levelManager.currentLevel == 1) *gameState = LEVEL;
		else if (levelManager.currentLevel == 2) *gameState = VICTORY;
	}

	if (player->position.y >= 600) *gameState = GAMEOVER;
}