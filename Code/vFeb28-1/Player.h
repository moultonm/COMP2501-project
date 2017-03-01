#pragma once
#include "Updateable.h"
#include "Renderable.h"
#include "defs.h"

class Player : public Updateable, public Renderable {
public:
	Player();
	~Player();

	void update(sf::Time); //player updates his position based on his velocity
	void jump(sf::Time);

	sf::Vector2f velocity;

	bool centered;
	bool isJumping;

	int groundLevel; //this will tell us how high we are jumping for now
	int jumpHeight;
	int speed; //the rate that velocity increments when the player moves
};
