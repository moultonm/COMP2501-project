#include "Enemy.h"

Enemy::Enemy(int x, int y) {
	accumulatedTime = sf::seconds(3);
	position.x = x;
	position.y = y;
	velocity.x = 0;
	velocity.y = 0;
	groundLevel = y;
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
	if (position.x < 0) velocity.x = +speed; //don't let the enemies leave the left bound of the screen
	sprite.setPosition(position);
}

void Enemy::update(sf::Time deltaTime, Player* p) {
	accumulatedTime += deltaTime;

	// move towards the player if they're within 200 pixels
	// attack player if they're within 100 pixels
	float ydiff = abs(p->position.y - position.y);

	if (p->position.x - this->position.x > -200 && p->position.x - this->position.x < 200 && ydiff < 175) {
		if (p->position.x < this->position.x) velocity.x = -speed;
		else velocity.x = +speed;
	}

	if (p->position.x - this->position.x > -300 && p->position.x - this->position.x < 300 && ydiff < 175) {
		if (accumulatedTime.asSeconds() >= 1) {
			this->attack(p);
			accumulatedTime = sf::seconds(0);
		}
	}

	position.x += velocity.x * deltaTime.asSeconds();
	position.y += velocity.y * deltaTime.asSeconds();
	if (position.x < 0) velocity.x = +speed; //don't let the enemies leave the left bound of the screen
	sprite.setPosition(position);

	//Enemies fall when they run off a platform
	if (position.y >= groundLevel) { //land gracefully when ground is touched
		position.y = groundLevel;
		velocity.y = 0;
	}
	else if (position.y < groundLevel) { //also fall if we walk off a platform
		velocity.y = speed;
	}
}


void Enemy::attack(Player* p) {
	float velx, vely, bulletOffset;

	if (p->position.x > this->position.x) {
		velx = Bullet::speed;
		vely = 0;
		bulletOffset = 15;
	}
	else {
		velx = -Bullet::speed;
		vely = 0;
		bulletOffset = -15;
	}
	bullets.push_back(new Bullet(position.x + bulletOffset, position.y + 10, velx, vely));
}