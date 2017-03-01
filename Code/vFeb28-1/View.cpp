#include "View.h"

View::View(Model* m) {
	model = m;

	width = 1024;
	height = 960;

	model->player->sprite.setTexture(imageManager.get_texture("Assets/tempPlayer.bmp", sf::Color(106, 76, 48)), true);

	//initialize our window
	window.create(sf::VideoMode(width, height), "COMP2501-Gooby_Space_Adventure");
	window.setFramerateLimit(45);

	//initializes title text for now
	font.loadFromFile("Assets/arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Green);
	text.setCharacterSize(28);
	text.setPosition(width / 4, height / 4);
	text.setString("Gooby's Space Adventure\n\n        (Press Space)");

	//background is just the same image repeated twice and it loops forever rightwards
	for (int i = 0; i < 2; i++) {
		backgroundSprites.push_back(sf::Sprite());
		backgroundSprites.back().setTexture(imageManager.get_texture("Assets/background.png"), true);
		backgroundSprites.back().setPosition((1024 * i) - (CENTER % 1024), 0);
	}
}

View::~View() {

}

void View::render() {
	window.clear(sf::Color::Black);

	if (*gameState == TITLE) {
		window.draw(text);
		window.display();
		return; //draw title screen, then exit the render call
	}

	/*-----draw the background-----*/
	if (model->player->centered) { //only scroll the background when player is center-screen
		backgroundSprites[0].setPosition(0 - ((int)model->player->position.x % 1024), 0); //modular position loops the background
		backgroundSprites[1].setPosition(1024 - ((int)model->player->position.x % 1024), 0);
	}
	window.draw(backgroundSprites[0]);
	window.draw(backgroundSprites[1]);

	/*-----handle the enemies-----*/
	for (int i = 0; i < model->enemies.size(); i++) {
		sf::Sprite enemy = model->enemies[i]->sprite;
		enemy.setTexture(imageManager.get_texture("Assets/goomba.bmp", sf::Color::White), true);
		if (model->player->centered) { //when player is centered, the goombas should not scroll with him..
			enemy.setPosition(CENTER + enemy.getPosition().x - model->player->position.x, enemy.getPosition().y);
		}
		window.draw(enemy);
	}

	/*-----render stuff-----*/
	for (int i = 0; i < renderables.size(); i++) {
		window.draw(renderables[i]->sprite);
	}

	window.display();
}