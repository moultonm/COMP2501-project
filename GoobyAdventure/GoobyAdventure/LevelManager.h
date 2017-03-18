#pragma once
#include <SFML/Graphics.hpp>
#include "Updateable.h"
#include "Enemy.h"
#include "Platform.h"
#include "Loot.h"
#include "Player.h"

class LevelManager : Updateable {
public:
	LevelManager();
	~LevelManager();
	void update(sf::Time);
	void generateLevel(int); //spawns the current level being played
	bool screenLimit(float);

	int currentLevel;
	int exitx, exity;

	sf::Time spawner; //accumulates time until we should spawn a new enemy
	Player* player;

	sf::RectangleShape exit;
	std::vector<Enemy*> enemies;
	std::vector<Loot*> loot;
	std::vector<Platform*> platforms; //its a platformer
};
