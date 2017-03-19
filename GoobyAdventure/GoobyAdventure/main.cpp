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

//Press ESC at any time to go back to the Level Select screen
// Enter chooses selected menu item
// W&S navigate menus
// A&D move left and right
// W jumps
// space shoots