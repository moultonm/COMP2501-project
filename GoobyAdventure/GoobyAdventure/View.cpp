#include "View.h"

View::View(Model* m) {
	model = m;

	width = 1024;
	height = 700;

	hud = new HUD();
	model->player->sprite.setTexture(imageManager.get_texture("Assets/tempPlayer.bmp", sf::Color(106, 76, 48)), true);

	//initialize our window
	window.create(sf::VideoMode(width, height), "COMP2501-Gooby_Space_Adventure");
	window.setFramerateLimit(45);

	//initializes title text for now
	font.loadFromFile("Assets/arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Magenta);
	text.setCharacterSize(28);
	text.setPosition(width / 4, height / 4);
	text.setString("Gooby's Space Adventure\n\n        (Press Space)");

	//background is just the same image repeated twice and it loops forever rightwards
	for (int i = 0; i < 2; i++) {
		backgroundSprites.push_back(sf::Sprite());
		backgroundSprites.back().setTexture(imageManager.get_texture("Assets/backgroundSmall.png"), true);
		backgroundSprites.back().setPosition((1024 * i) - (CENTER_SCREEN % 1024), 0);
	}
}

View::~View() {

}

void View::render() {
	window.clear(sf::Color::Black);

	if (*gameState == TITLE) {
		window.draw(text);
		window.display();
	}
	else if (*gameState == CRAFT) {
		model->crafting->menu(model->items);
		model->crafting->render(&window);
		window.display();
	}
	else if (*gameState == LEVEL) {
		model->levelScreen->render(&window);
		window.display();
	}
	if (*gameState != GAME) {
		return; //don't draw anything else if we haven't started the game yet
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
			enemy.setPosition(CENTER_SCREEN + enemy.getPosition().x - model->player->position.x, enemy.getPosition().y);
		}
		window.draw(enemy);
	}

	/*-----draw platforms------*/
	for (int i = 0; i < model->platforms.size(); i++) {
		sf::RectangleShape plat = model->platforms[i]->plat;
		if (model->player->centered) { //when player is centered, the platforms should not scroll with him..
			plat.setPosition(CENTER_SCREEN + plat.getPosition().x - model->player->position.x, plat.getPosition().y);
		}
		window.draw(plat);
	}

	/*-----render stuff-----*/
	for (int i = 0; i < renderables.size(); i++) {
		window.draw(renderables[i]->sprite);
	}

	ss.str(""); //clear and update score UI
	ss << "Score: " << model->score;
	text.setString(ss.str());
	hud->render(&window);
	window.draw(text);
	window.display();
}

/*
//SCROLL THE MIDGROUND TILES
for (int i = 0; i < model->mapRows; i++) {
for (int j = 0; j < model->mapCols; j++) {
mapSprites[i][j].setPosition((j * xOffset) + (MID_X)-(model->player->x*xOffset), (i * yOffset) + (MID_Y)-(model->player->y*yOffset));
}
}

//ENEMIES
for (int i = 0; i < model->enemies.size(); i++) {
sf::Sprite currEnemy = model->enemies[i]->sprite;
currEnemy.setTexture(enemyTexture);
currEnemy.setPosition((model->enemies[i]->x*xOffset) + (MID_X + 32) - (model->player->x * xOffset), (model->enemies[i]->y*yOffset) + (MID_Y + 32) - (model->player->y*yOffset));
window.draw(currEnemy);
}

//BULLETS
for (int i = 0; i < model->player->bullets.size(); i++) {
sf::Sprite currBullet = model->player->bullets[i]->sprite;
currBullet.setTexture(bulletTexture);
currBullet.setPosition((model->player->bullets[i]->x*xOffset) + (MID_X + 32) - (model->player->x * xOffset), (model->player->bullets[i]->y*yOffset) + (MID_Y + 32) - (model->player->y*yOffset));
window.draw(currBullet);
}

std::stringstream ss;
ss.str("");
ss << "Score: " << model->score;
text.setString(ss.str()); //displays the score during the game

//TEXT
font.loadFromFile("Assets/arial.ttf");
text.setFont(font);
text.setFillColor(sf::Color::Magenta);
text.setCharacterSize(14);
text.setPosition(5, 5);
*/