#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Model.h"
#include "View.h"
#include "Control.h"

class Game {
public:
	Game();
	~Game();

	void loop(); //run through the game loop until we quit

	sf::Clock clock;

	int gameState; //title screen, game screen, ...

private:
	Model* model; //our game world
	View* view; //the visual representation
	Control* control; //player inputs
};
