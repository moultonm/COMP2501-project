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


//might want to try setting origin of sprites to their center if we want circle collision (or easier to just move the center in the collision code?)
//i might not have to change the way things are drawn if i just set everythings origin.. they all get bumped a bit up-left but that might be ok