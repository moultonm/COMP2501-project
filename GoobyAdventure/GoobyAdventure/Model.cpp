#include "Model.h"

Model::Model() {
	spawner = sf::seconds(0);
	score = 0;
	crafting = new Crafting();
	levelScreen = new LevelScreen();
	items.reserve(5);
	items.push_back(new Item(1, "bullet"));
	items.push_back(new Item(1, "flux capacitor"));

	//make some platforms just to try em out
	for (int i = 0; i < 20; i++) {
		platforms.push_back(new Platform(240 * i, rand() % 116 + 532, rand() % 110 + 50, rand() % 50 + 10));
	}
}

Model::~Model() {

}

void Model::update(sf::Time deltaTime) {
	if (*gameState != GAME) {
		return; //don't update anything if we haven't started the game yet
	}

	/*-----spawn new enemies into the game-----*/
	spawner += deltaTime;
	if (spawner.asSeconds() > 4) { //every 4 seconds
		enemies.push_back(new Enemy(rand() % (2 * CENTER_SCREEN))); //spawn a new enemy randomly on the screen
		spawner = sf::seconds(0);
	}

	/*-----updateables-----*/
	for (int i = 0; i < updateables.size(); i++) {
		updateables[i]->update(deltaTime);
	}

	/*-----check if player is on a platform-----*/
	for (int i = 0; i < platforms.size(); i++) {
		if (player->position.x + 60 > platforms[i]->x && player->position.x + 40 < platforms[i]->x + platforms[i]->width
			&& player->position.y + 75 <= platforms[i]->y) { //have to mess with the player's coordinates since the sprite is crappy
			player->groundLevel = platforms[i]->y - 75; //set groundlevel to the platform we are on (-75 is to match the sprites feet instead of his top box)
			break;
		}
		else if (!(player->position.x + 35 > platforms[i]->x && player->position.x + 35 < platforms[i]->x + platforms[i]->width)) { //reset groundlevel if we aren't on a platform
			player->groundLevel = 600; //this value is the "floor" level, can be updated for each level once levels are designed

		}
	}

	/*-----update enemies-----*/
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update(deltaTime);
		/*-----attempt to kill enemy by jumping on him-----*/
		if (player->isJumping && player->position.y + 22 > enemies[i]->position.y - 65 && player->position.y + 22 < enemies[i]->position.y + 15 &&
			player->position.x + 35 > enemies[i]->position.x + 10 && player->position.x + 35 < enemies[i]->position.x + 94) { //temporary magic numbers are to tighten the hitbox since the sprites aren't boxed well
			enemies.erase(enemies.begin() + i); //remove this enemy from the game
			score += 50;
		}
	}
}

/*
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

//UPDATE ENEMIES
for (int i = 0; i < enemies.size(); i++) {
if (enemies[i]->x > player->x) {
enemies[i]->velocity.x = -enemies[i]->speed;
}
else {
enemies[i]->velocity.x = enemies[i]->speed;
}
if (enemies[i]->y > player->y) {
enemies[i]->velocity.y = -enemies[i]->speed;
}
else {
enemies[i]->velocity.y = enemies[i]->speed;
}
enemies[i]->update(deltaTime);
}

//CHECK COLLISION WITH BULLETS
for (int i = 0; i < player->bullets.size(); i++) {
for (int j = 0; j < enemies.size(); j++) {
if (pow(player->bullets[i]->x * 64 - enemies[j]->x * 64, 2) +
pow(player->bullets[i]->y * 64 - enemies[j]->y * 64, 2) <=
pow(RADIUS_BUL + RADIUS_EN, 2)) {
player->bullets.erase(player->bullets.begin() + i);
enemies.erase(enemies.begin() + j);
score += 50;
break;
}
}
}

//CHECK COLLISION WITH PLAYER
for (int j = 0; j < enemies.size(); j++) {
if (pow(player->x * 64 - enemies[j]->x * 64, 2) +
pow(player->y * 64 - enemies[j]->y * 64, 2) <=
pow(RADIUS_BUL + RADIUS_EN, 2)) {
*gameState = 2; //game over
break;
}
}



*/