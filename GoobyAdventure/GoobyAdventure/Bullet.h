#pragma once
#include "Updateable.h"
#include "Renderable.h"

class Bullet : public Updateable, public Renderable {
public:
	Bullet(float, float, float, float);
	~Bullet();

	void update(sf::Time);

	sf::Vector2f velocity;
	const static int speed = 7;

	float timeToLive;
};
