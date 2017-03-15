#include "Bullet.h"

Bullet::Bullet(float x, float y, float velx, float vely) {
	position.x = x;
	position.y = y;
	velocity.x = velx;
	velocity.y = vely;
	timeToLive = 2; //bullets will fly for 2 seconds before despawning
	//sprite.setOrigin(32, 32);
}

Bullet::~Bullet() {
}

void Bullet::update(sf::Time deltaTime) {
	position.x += velocity.x * deltaTime.asSeconds();
	position.y += velocity.y * deltaTime.asSeconds();
	timeToLive -= deltaTime.asSeconds();
	sprite.setPosition(position);
}