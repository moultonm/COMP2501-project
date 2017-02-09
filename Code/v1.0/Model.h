#pragma once
#include <SFML/System.hpp>
#include "Updateable.h"
#include "Player.h"
#include "defs.h"

class Model {
public:
	Model();
	~Model();

	void update(sf::Time); //updateables are updated with respect to delta time

	std::vector<Updateable*> updateables; //collection of objects to be updated

	Player* player; //a pointer to our player

	int* gameState; //keeps track of global gamestate in model
};
