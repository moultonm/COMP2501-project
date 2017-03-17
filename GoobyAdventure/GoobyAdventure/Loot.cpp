#include "Loot.h"

Loot::Loot(float x, float y) {
	this->x = x;
	this->y = y;
	looted = false;
	value = 10;
	sprite.setPosition(x, y);
}

Loot::~Loot() {

}