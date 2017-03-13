#include "Player.h"

Player::Player() {

	groundLevel = 600;
	position.x = 15;
	position.y = groundLevel;
	centered = false;
	isJumping = false;

	velocity.x = 0;
	velocity.y = 0;

	speed = 250;
	jumpSpeed = 400;
	jumpHeight = 150;
	jumpLocation = groundLevel;
}

Player::~Player() {

}

void Player::update(sf::Time deltaTime) {

	if (sprite.getPosition().x >= CENTER_SCREEN) { //once we leave the left edge, the camera is locked on the player
		centered = true;
	}
	if (position.x <= CENTER_SCREEN) { //if we are at the left edge of the world, stop the camera (so we don't see black background)
		centered = false;
	}

	position.x += velocity.x * deltaTime.asSeconds();
	if (position.x < 0) position.x = 0; //don't let the player leave the left bound of the screen

	jump(deltaTime); //player jumps!

	if (!centered) { //this gives us the effect where the player moves until he is centered, after which the camera moves instead of the player
		sprite.setPosition(position);
	}
	else { //still need to update the Y position for jumps
		sprite.setPosition(CENTER_SCREEN, position.y);
	}
}

void Player::jump(sf::Time deltaTime) {
	/*-----JUMPING TIME!-----*/
	position.y += velocity.y * deltaTime.asSeconds();
	if (position.y >= groundLevel) { //land gracefully when ground is touched
		position.y = groundLevel;
		isJumping = false;
		velocity.y = 0;
	}
	else if (isJumping && position.y <= jumpLocation - jumpHeight) { //fall once we reach the apex of the jump
		velocity.y = jumpSpeed * 1.25;
	}
	else if (!isJumping && groundLevel == 600 && position.y < 600) { //also fall if we walk off a platform
		velocity.y = jumpSpeed * 1.25;
	}
}


/*
void Player::fireBullet() {
float velx, vely;
//set these based on facing direction
if (facing == 0) {
velx = Bullet::speed;
vely = 0;
}
else if (facing == 1) {
velx = 0;
vely = -Bullet::speed;
}
else if (facing == 2) {
velx = -Bullet::speed;
vely = 0;
}
else if (facing == 3) {
velx = 0;
vely = Bullet::speed;
}
bullets.push_back(new Bullet(x, y, velx, vely));
}

*/