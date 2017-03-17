GOOBY'S SPACE ADVENTURE

Authors:
Alexandra Wilson (100998162)
Matthew Moulton (101010631)

Bugs in this version:
- Player sprite is 'falling' instead of 'standing' while on moving platform
- Player sprite is always right-facing when 'falling' (but its fine when jumping)
- Camera draws the wrong platforms when you reach the upper-left part of the level

CONTROLS:
- From Title Screen: Space to start game
- From Level Select: W/S to change selection, Enter to choose selection
- From Crafting Screen: W/S to change selection, Enter to choose selection
- Gameplay: A/D to move left and right, W to jump

DEPENDENCIES:
- standard sfml setup, but MAKE SURE you include "sfml-audio.lib" and
  "sfml-audio-d.lib" now so you don't run into issues with music later!!!!


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
