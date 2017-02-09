#pragma once
#include "Updateable.h"
#include "Renderable.h"

class Player : public Updateable, public Renderable {
public:
	Player();
	~Player();

	void update(sf::Time); //player updates his position based on his velocity

	sf::Vector2f velocity;

	int speed; //the rate that velocity increments when the player moves
};
