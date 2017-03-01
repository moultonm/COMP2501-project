#include "Player.h"

Player::Player() {

	groundLevel = 820;
	position.x = 15;
	position.y = groundLevel;
	centered = false;
	isJumping = false;

	velocity.x = 0;
	velocity.y = 0;

	speed = 200;
	jumpHeight = 150;
}

Player::~Player() {

}

void Player::update(sf::Time deltaTime) {

	if (sprite.getPosition().x >= CENTER) { //once we leave the left edge, the camera is locked on the player
		centered = true;
	}
	if (position.x <= CENTER) { //if we are at the left edge of the world, stop the camera (so we don't see black background)
		centered = false;
	}


	position.x += velocity.x * deltaTime.asSeconds();
	if (position.x < 0) position.x = 0; //don't let the player leave the left bound of the screen

	jump(deltaTime); //player jumps!

	if (!centered) { //this gives us the effect where the player moves until he is centered, after which the camera moves instead of the player
		sprite.setPosition(position);
	}
	else { //still need to update the Y position for jumps
		sprite.setPosition(CENTER, position.y);
	}
}

void Player::jump(sf::Time deltaTime) {
	/*-----JUMPING TIME!-----*/
	if (position.y <= groundLevel - jumpHeight && velocity.y < 0) velocity.y *= -1; //player comes back down after a 150 unit jump
	if (isJumping) {
		position.y += velocity.y * deltaTime.asSeconds(); //now we move him in the air
		if (position.y >= groundLevel) { //and he lands gracefully when he touches back down
			position.y = groundLevel;
			isJumping = false;
		}
	}
}