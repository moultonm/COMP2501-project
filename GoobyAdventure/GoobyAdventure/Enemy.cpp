#include "Enemy.h"

Enemy::Enemy() {
	Enemy(CENTER_SCREEN); //defaults our enemy to the middle of the screen
}

Enemy::Enemy(int x) {
	accumulatedTime = sf::seconds(0);
	position.x = x;
	position.y = 600;
	velocity.x = 0;
	velocity.y = 0;
	speed = 125;
}

Enemy::~Enemy() {

}

void Enemy::update(sf::Time deltaTime) {
	accumulatedTime += deltaTime;

	if (accumulatedTime.asSeconds() > 4) { //every 4 seconds
		if (rand() % 2 == 0) { //enemy randomly starts moving left or right
			velocity.x = +speed;
		}
		else {
			velocity.x = -speed;
		}
		accumulatedTime = sf::seconds(0);
	}

	position.x += velocity.x * deltaTime.asSeconds();
	sprite.setPosition(position);
}
