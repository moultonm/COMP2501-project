#include "Enemy.h"

Enemy::Enemy(int x, int y) {
	accumulatedTime = sf::seconds(3);
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
	std::cout << "I'm in here!!!" << std::endl;
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

	if (p->position.x - this->position.x > -200 && p->position.x - this->position.x < 200) { //enemy randomly starts moving left or right
		if (p->position.x < this->position.x) velocity.x = -speed;
		else velocity.x = +speed;
	}

	if (p->position.x - this->position.x >-300 && p->position.x - this->position.x < 300) {
		if (accumulatedTime.asSeconds() >= 1) {
			this->attack(p);
			accumulatedTime = sf::seconds(0);
		}
	}

	position.x += velocity.x * deltaTime.asSeconds();
	if (position.x < 0) velocity.x = +speed; //don't let the enemies leave the left bound of the screen
	sprite.setPosition(position);
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