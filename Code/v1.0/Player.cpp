#include "Player.h"

Player::Player() {
	position.x = 0;
	position.y = 0;

	velocity.x = 0;
	velocity.y = 0;

	speed = 200;
}

Player::~Player() {

}

void Player::update(sf::Time deltaTime) {

	position.x += velocity.x * deltaTime.asSeconds();
	position.y += velocity.y * deltaTime.asSeconds();

	sprite.setPosition(position);
}
