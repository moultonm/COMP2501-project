#include "Enemy.h"

Enemy::Enemy() {
	Enemy(CENTER_SCREEN, 600); //defaults our enemy to the middle of the screen
}

Enemy::Enemy(int x, int y) {
	accumulatedTime = sf::seconds(0);
	position.x = x;
	position.y = y;
	velocity.x = 0;
	velocity.y = 0;
	speed = 125;
	//sprite.setOrigin(52, 54);
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
	if (position.x < 0) velocity.x = +speed; //don't let the enemies leave the left bound of the screen
	sprite.setPosition(position);
}
