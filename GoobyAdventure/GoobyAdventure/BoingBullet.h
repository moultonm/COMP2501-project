#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"

class BoingBullet : public Bullet{
public:
	BoingBullet(float x = 0, float y = 0, float velx = 0, float vely = 0);
	~BoingBullet();


private:

};