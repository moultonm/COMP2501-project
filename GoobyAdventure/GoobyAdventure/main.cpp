/*
Project: COMP2501A - Final Project - Gooby's Space Adventure
Authors: Alexandra Wilson (100998162), Matthew Moulton (101010631)
*/
#include "Game.h"

int main() {
	srand(time(0)); //random seed based on current time
	Game game;

	game.loop();

	return 0;
}