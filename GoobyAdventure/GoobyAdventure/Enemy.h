#pragma once
#include "Updateable.h"
#include "Renderable.h"
#include "defs.h"

class Enemy : public Updateable, public Renderable {
public:
	Enemy();
	Enemy(int); //constructs our enemy at a given x coordinate
	~Enemy();

	void update(sf::Time); //Enemy updates his position based on his velocity?

	sf::Vector2f velocity;

	int speed; //the rate that velocity increments when the Enemy moves
	sf::Time accumulatedTime; //enemy may change behaviour after some time passes
};
