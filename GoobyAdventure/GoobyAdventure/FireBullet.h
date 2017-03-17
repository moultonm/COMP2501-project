#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Bullet.h"

class FireBullet : public Bullet {
public:
	FireBullet(float x=0, float y=0, float velx=0, float vely=0);
	~FireBullet();

private:

};