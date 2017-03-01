#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include "Model.h"
#include "Renderable.h"
#include "Manager.h"

class View {
public:
	View(Model*); //there should only be 1 model, so this takes a reference to the model created in Game
	~View();

	void render(); //draws renderable objects to the screen

	int width, height; //window resolution size
	sf::RenderWindow window; //our friend the game window

	std::vector<Renderable*> renderables; //collection of objects to be drawn

	//we can write things on the screen! does this go here?
	sf::Font font;
	sf::Text text;
	std::stringstream ss;

	int* gameState; //keeps track of global gamestate in view

	Manager imageManager; //loads textures as they are needed (maybe implement unloading someday)

	std::vector<sf::Sprite> backgroundSprites;

private:
	Model* model;
};
