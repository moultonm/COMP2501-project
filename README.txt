GOOBY'S SPACE ADVENTURE

Authors:
Alexandra Wilson (100998162)
Matthew Moulton (101010631)

DEPENDENCIES:
- standard sfml setup, but MAKE SURE you include "sfml-audio.lib" and
  "sfml-audio-d.lib" now so you don't run into issues with music later!!!!
  
Notes:
- The project directory I zipped and uploaded can be individually downloaded from github if you click on it. It assumes you have your SFML folder saved at "C:\SFML-2.4.1"
- If you already have your own project created, just plop the source code files in there, and put the stuff from "Assets" in a directory called "Assets" in the same directory as your source code (it looks for the textures at that spot)

UPDATES AS OF MARCH 4 AT 12:47 AM:
- by Alex-

- this code has a working crafting system and a working level selection screen
- changes to PLAYER:
	- took the items vector away from the player
- changes to MODEL:
	- gave a levelscreen and crafting obj
	- gave an items vector
- changes to VIEW:
	 - added a few extra lines of code to properly display new screens
- changes to CONTROL:
	- so so so much
	- changed the way that some of the key press events are listened for in inputs
	- added level screen and crafting control via input
	- oh sweet neptune there's a lot of code
- changes to DEFS:
	- added a couple of game states

Source Files:
main.cpp
Game.cpp
Model.cpp
View.cpp
Control.cpp
Manager.cpp
Player.cpp
Enemy.cpp
Crafting.cpp
Item.cpp
LevelScreen.cpp
Platform.cpp

Header Files:
Game.h
Model.h
View.h
Control.h
Manager.h
Player.h
Renderable.h
Updateable.h
defs.h
Crafting.h
Enemy.h
Item.h
LevelScreen.h
Platform.h
