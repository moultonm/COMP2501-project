#pragma once
#include "Updateable.h"
#include "Renderable.h"
#include "defs.h"
#include "Player.h"
#include "Bullet.h"
#include "FireBullet.h"
#include "BoingBullet.h"
#include <cmath>
#include <iostream>
#include <vector>

class Enemy : public Updateable, public Renderable {
public:
	Enemy(int x = CENTER_SCREEN, int y = 600); //constructs our enemy at a given x,y coordinate
	~Enemy();

	virtual void update(sf::Time); //Enemy updates his position based on his velocity?
	void update(sf::Time, Player* p);
	void attack(Player* p);

	sf::Vector2f velocity;
	std::vector<Bullet*> bullets;

	int speed; //the rate that velocity increments when the Enemy moves
	sf::Time accumulatedTime; //enemy may change behaviour after some time passes
};
