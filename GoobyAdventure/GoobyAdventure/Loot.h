#pragma once
#include "Renderable.h"

class Loot : public Renderable {
public:
	Loot(float, float);
	~Loot();

	float x, y;
	bool looted;
	int value;
};
