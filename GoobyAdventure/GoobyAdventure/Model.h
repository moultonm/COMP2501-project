#pragma once
#include <SFML/System.hpp>
#include "Updateable.h"
#include "Player.h"
#include "Enemy.h"
#include "defs.h"
#include "Crafting.h"
#include "Platform.h"
#include "LevelScreen.h"
#include "LevelManager.h"

class Model {
public:
	Model();
	~Model();

	void update(sf::Time); //updateables are updated with respect to delta time

	std::vector<Updateable*> updateables; //collection of objects to be updated

	Player* player; //a pointer to our player
	Crafting* crafting; // this is a pointer to the crafting menu
	LevelScreen* levelScreen;

	LevelManager levelManager;

	int* gameState; //keeps track of global gamestate in model
	int score;

	std::vector<Item*> items;

	int counter;
};
