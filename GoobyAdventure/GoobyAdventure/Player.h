#pragma once
#include <vector>
#include "Updateable.h"
#include "Renderable.h"
#include "defs.h"
#include "Item.h"
#include "Bullet.h"

class Player : public Updateable, public Renderable {
public:
	Player();
	~Player();

	void update(sf::Time); //player updates his position based on his velocity
	void jump(sf::Time);
	void fireBullet();
	//facing - holds direction so we know which way to fire bullets? also sprite flipping
	int facing;
	std::vector<Bullet*> bullets;

	sf::Vector2f velocity;

	bool centered; //is the camera centered on the player?
	bool centeredY; //vertical centering
	bool isJumping;
	bool isMoving;

	int counter;

	int groundLevel; //the height the player belongs at (no flying allowed!!) -> maybe this is an attribute of the level instead of player later
	int jumpHeight;
	int jumpLocation; //stores initial height jumped from
	int speed; //the rate that velocity increments when the player moves
	int jumpSpeed;
};
