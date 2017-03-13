#pragma once
#include "Model.h"
#include "View.h"
#include "defs.h"

class Control {
public:
	Control(Model*, View*); //only one of each MVC should exist, so we take references to the ones created in game
	~Control();

	void inputs(); //takes user input and changes game world based on it

	int* gameState; //keeps track of global gamestate in controller

private:
	Model* model;
	View* view;
};
