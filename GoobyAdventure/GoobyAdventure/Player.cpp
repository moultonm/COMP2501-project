#include "Player.h"

Player::Player() {

	groundLevel = 600;
	position.x = 15;
	position.y = groundLevel-50;
	centered = false;
	centeredY = false;
	isJumping = false;

	velocity.x = 0;
	velocity.y = 0;

	counter = 0;

	coins = 0;
	facing = 0;
	armour = 2;
	speed = 250;
	jumpSpeed = 400;
	jumpHeight = 150;
	jumpLocation = groundLevel;
	//sprite.setOrigin(48, 44); //48 44
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
	if (sprite.getPosition().y <= 350) {
		centeredY = true;
	}
	if (position.y >= 350) {
		centeredY = false;
	}

	position.x += velocity.x * deltaTime.asSeconds();
	if (position.x < 0) position.x = 0; //don't let the player leave the left bound of the screen

	jump(deltaTime); //player jumps!

	if (!centered && !centeredY) { //this gives us the effect where the player moves until he is centered, after which the camera moves instead of the player
		sprite.setPosition(position);
	}
	else if (!centered && centeredY) {
		sprite.setPosition(position.x, 350);
	}
	else if (centered && !centeredY) {
		sprite.setPosition(CENTER_SCREEN, position.y);
	}
	else { //still need to update the Y position for jumps
		sprite.setPosition(CENTER_SCREEN, 350);
	}
}

void Player::jump(sf::Time deltaTime) {
	/*-----JUMPING TIME!-----*/
	position.y += velocity.y * deltaTime.asSeconds();
	if (isJumping) { // jumping sprite. Depends on which direction the player is facing

		if (facing == 0) { sprite.setTextureRect(sf::IntRect(438, 93, 67, 94)); }
		else { sprite.setTextureRect(sf::IntRect(505, 93, -67, 94)); }
	}
	else {
		if (isMoving && position.y == groundLevel) { // running sprites
			if (facing == 0) {
				if (counter >= 50) {
					sprite.setTextureRect(sf::IntRect(292, 98, 72, 97)); counter = 0;
				}
				else if (counter >= 45) {
					sprite.setTextureRect(sf::IntRect(365, 0, 72, 97));
				}
				else if (counter >= 40) {
					sprite.setTextureRect(sf::IntRect(219, 98, 72, 97));
				}
				else if (counter >= 35) {
					sprite.setTextureRect(sf::IntRect(292, 0, 72, 97));
				}
				else if (counter >= 30) {
					sprite.setTextureRect(sf::IntRect(219, 0, 72, 97));
				}
				else if (counter >= 25) {
					sprite.setTextureRect(sf::IntRect(146, 98, 72, 97));
				}
				else if (counter >= 20) {
					sprite.setTextureRect(sf::IntRect(73, 98, 72, 97));
				}
				else if (counter >= 15) {
					sprite.setTextureRect(sf::IntRect(0, 98, 72, 97));
				}
				else if (counter >= 10) {
					sprite.setTextureRect(sf::IntRect(146, 0, 72, 97));
				}
				else if (counter >= 5) {
					sprite.setTextureRect(sf::IntRect(73, 0, 72, 97));
				}
				else {
					sprite.setTextureRect(sf::IntRect(0, 0, 72, 97));
				}
			}
			else { // running sprites in the left direction
				if (counter >= 50) {

					sprite.setTextureRect(sf::IntRect(364, 98, -72, 97)); counter = 0;
				}
				else if (counter >= 45) {
					sprite.setTextureRect(sf::IntRect(437, 0, -72, 97));
				}
				else if (counter >= 40) {
					sprite.setTextureRect(sf::IntRect(291, 98, -72, 97));
				}
				else if (counter >= 35) {
					sprite.setTextureRect(sf::IntRect(364, 0, -72, 97));
				}
				else if (counter >= 30) {
					sprite.setTextureRect(sf::IntRect(291, 0, -72, 97));
				}
				else if (counter >= 25) {
					sprite.setTextureRect(sf::IntRect(218, 98, -72, 97));
				}
				else if (counter >= 20) {
					sprite.setTextureRect(sf::IntRect(145, 98, -72, 97));
				}
				else if (counter >= 15) {
					sprite.setTextureRect(sf::IntRect(72, 98, -72, 97));
				}
				else if (counter >= 10) {
					sprite.setTextureRect(sf::IntRect(218, 0, -72, 97));
				}
				else if (counter >= 5) {
					sprite.setTextureRect(sf::IntRect(145, 0, -72, 97));
				}
				else {
					sprite.setTextureRect(sf::IntRect(72, 0, -72, 97));
				}
			}
			counter++;
		}
		else if (!isMoving && position.y == groundLevel) { // standing
			if (facing == 0) sprite.setTextureRect(sf::IntRect(67, 196, 66, 92));
			else sprite.setTextureRect(sf::IntRect(133, 196, -66, 92));
		}
		else { // falling
			if (facing == 0) { sprite.setTextureRect(sf::IntRect(438, 93, 67, 94)); }
			else { sprite.setTextureRect(sf::IntRect(505, 93, -67, 94)); }
		}
	}

	if (position.y >= groundLevel) { //land gracefully when ground is touched
		position.y = groundLevel;

		isJumping = false;
		velocity.y = 0;
	}
	else if (isJumping && position.y <= jumpLocation - jumpHeight) { //fall once we reach the apex of the jump
		velocity.y = jumpSpeed * 1.25;
	}
	else if (!isJumping && position.y < groundLevel) { //also fall if we walk off a platform   //groundLevel == 600 && position.y < 600
		sprite.setTextureRect(sf::IntRect(438, 93, 67, 94));
		velocity.y = jumpSpeed * 1.25;
	}
}

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
	bullets.push_back(new Bullet(position.x, position.y, velx, vely));
}

