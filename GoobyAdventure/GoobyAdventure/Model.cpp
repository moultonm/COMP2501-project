#include "Model.h"

Model::Model() {
	score = 0;
	crafting = new Crafting();
	levelScreen = new LevelScreen();
	items.reserve(5);
	items.push_back(new Item(1, "bullet"));
	items.push_back(new Item(1, "flux capacitor"));
}

Model::~Model() {

}

void Model::update(sf::Time deltaTime) {
	if (*gameState != GAME) {
		return; //don't update anything if we haven't started the game yet
	}


	/*-----spawn new enemies into the game-----*/
	levelManager.update(deltaTime);

	/*-----updateables-----*/
	for (int i = 0; i < updateables.size(); i++) {
		updateables[i]->update(deltaTime);
	}

	/*-----check if player is on a platform-----*/
	bool gotOne = false;
	for (int i = 0; i < levelManager.platforms.size(); i++) {
		if (player->position.x + 40 > levelManager.platforms[i]->x && player->position.x + 25 < levelManager.platforms[i]->x + levelManager.platforms[i]->width
			&& player->position.y + 90 <= levelManager.platforms[i]->y) { //have to mess with the player's coordinates since the sprite is crappy
			player->groundLevel = levelManager.platforms[i]->y - 90; //set groundlevel to the platform we are on (-90 is to match the sprites feet instead of his top box)
			gotOne = true;
		}
		else if (!gotOne) {//!(player->position.x + 40 > levelManager.platforms[i]->x && player->position.x + 25 < levelManager.platforms[i]->x + levelManager.platforms[i]->width)) { //reset groundlevel if we aren't on a platform
			player->groundLevel = 600; //this value is the "floor" level, can be updated for each level once levels are designed
		}
	}

	/*-----update enemies-----*/
	for (int i = 0; i < levelManager.enemies.size(); i++) {
		levelManager.enemies[i]->update(deltaTime);
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
	}

	//UPDATE BULLETS
	for (int i = 0; i < player->bullets.size(); i++) {
		player->bullets[i]->update(deltaTime);
	}

	//CHECK COLLISION WITH BULLETS
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

	//CHECK COLLISION WITH PLAYER
	for (int j = 0; j < levelManager.enemies.size(); j++) {
		player->sprite.setColor(sf::Color::Green);
		if (pow((player->position.x + 40) - (levelManager.enemies[j]->position.x + 52), 2) +
			pow((player->position.y + 61) - (levelManager.enemies[j]->position.y + 54), 2) <=
			pow(25 + 26, 2)) {
			//*gameState = 2; //game over
			player->sprite.setColor(sf::Color::Red); //for now show collision by updating color
			break;
		}
	}
} //bullet center 32,32 radius 32
//enemy center 52,54 .. 26 radius
//player center ?,?   radius ?