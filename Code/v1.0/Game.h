#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Model.h"
#include "View.h"
#include "Control.h"
#include "Manager.h"

class Game {
public:
	Game();
	~Game();

	void loop(); //run through the game loop until we quit

	sf::Clock clock;

	Manager imageManager; //loads textures as they are needed (maybe implement unloading someday)

	int gameState; //title screen, game screen, ...

private:
	Model* model; //our game world
	View* view; //the visual representation
	Control* control; //player inputs
};
