GOOBY'S SPACE ADVENTURE

Authors:
Alexandra Wilson (100998162)
Matthew Moulton (101010631)

FIXED in this version:
- fixed level two's moving platform
- fixed background drawing properly between levels
- game ends when the last exit is touched
- added little story text part
- dies now when you fall in pit
- take damage when bullets hit you (and end game when dead)
- fixed styling of topleft statistics (and display armour value)
- changed coin to a different graphic

CONTROLS:
- Press ESC at any time to go back to Level Select menu
- From Title Screen: Space to start game
- From Level Select: W/S to change selection, 'Enter' to choose selection
- From Crafting Screen: W/S to change selection, 'Enter' to choose selection
- Gameplay: A/D to move left and right, W to jump, Space to shoot

DEPENDENCIES:
- standard sfml setup

~~~Source Files:
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
BoingBullet.cpp
Bullet.cpp
FireBullet.cpp
HUD.cpp
LevelManager.cpp
Loot.cpp

~~~Header Files:
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
BoingBullet.h
Bullet.h
FireBullet.h
HUD.h
LevelManager.h
Loot.h
