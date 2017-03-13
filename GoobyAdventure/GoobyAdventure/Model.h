#pragma once
#include <SFML/System.hpp>
#include "Updateable.h"
#include "Player.h"
#include "Enemy.h"
#include "defs.h"
#include "Crafting.h"
#include "Platform.h"
#include "LevelScreen.h"

class Model {
public:
	Model();
	~Model();

	void update(sf::Time); //updateables are updated with respect to delta time

	std::vector<Updateable*> updateables; //collection of objects to be updated

	Player* player; //a pointer to our player
	Crafting* crafting; // this is a pointer to the crafting menu
	LevelScreen* levelScreen;

	int* gameState; //keeps track of global gamestate in model
	int score;

	sf::Time spawner; //accumulates time until we should spawn a new enemy
	std::vector<Enemy*> enemies;

	std::vector<Platform*> platforms; //its a platformer
	std::vector<Item*> items;
};
