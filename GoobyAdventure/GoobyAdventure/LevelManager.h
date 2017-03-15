#pragma once
#include <SFML/Graphics.hpp>
#include "Updateable.h"
#include "Enemy.h"
#include "Platform.h"

class LevelManager : Updateable {
public:
	LevelManager();
	~LevelManager();
	void update(sf::Time);
	void generateLevel(int); //spawns the current level being played

	int currentLevel;

	sf::Time spawner; //accumulates time until we should spawn a new enemy
	std::vector<Enemy*> enemies;

	std::vector<Platform*> platforms; //its a platformer
};
