#include "View.h"

View::View(Model* m) {
	model = m;

	width = 1024;
	height = 700;

	hud = new HUD();
	model->player->sprite.setTexture(imageManager.get_texture("Assets/p1_spritesheet.png"));
	model->player->sprite.setTextureRect(sf::IntRect(67, 196, 66, 92));

	//initialize our window
	window.create(sf::VideoMode(width, height), "COMP2501-Gooby_Space_Adventure");
	window.setFramerateLimit(45);

	//initializes title text for now
	font.loadFromFile("Assets/Escalope_Crust-One.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Magenta);
	text.setCharacterSize(65);
	text.setPosition(width / 4, height / 4);
	text.setString("Gooby's Space Adventure\n\n        (Press Space)");

	//background is just the same image repeated twice and it loops forever rightwards
	for (int i = 0; i < 2; i++) { //GRASSY BACKGROUND
		backgroundSprites.push_back(sf::Sprite());
		backgroundSprites.back().setTexture(imageManager.get_texture("Assets/backgroundSmall.png"), true);
		backgroundSprites.back().setPosition((1024 * i) - (CENTER_SCREEN % 1024), 0);
	}
	for (int i = 0; i < 2; i++) { //THIS IS THE UPPER BACKGROUND
		backgroundSprites.push_back(sf::Sprite());
		backgroundSprites.back().setTexture(imageManager.get_texture("Assets/starfield.png"), true);
		backgroundSprites.back().setPosition((1024 * i) - (CENTER_SCREEN % 1024), -700);
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
		backgroundSprites[0].setPosition(0 - ((int)model->player->position.x % width), 0); //modular position loops the background
		backgroundSprites[1].setPosition(1024 - ((int)model->player->position.x % width), 0);
		backgroundSprites[2].setPosition(0 - ((int)model->player->position.x % width), -height);
		backgroundSprites[3].setPosition(1024 - ((int)model->player->position.x % width), -height);
	}
	if (model->player->position.y < height / 2) {
		backgroundSprites[0].setPosition(backgroundSprites[0].getPosition().x, height / 2 - model->player->position.y);
		backgroundSprites[1].setPosition(backgroundSprites[1].getPosition().x, height / 2 - model->player->position.y);
		backgroundSprites[2].setPosition(backgroundSprites[2].getPosition().x, -height + height / 2 - model->player->position.y);
		backgroundSprites[3].setPosition(backgroundSprites[3].getPosition().x, -height + height / 2 - model->player->position.y);
	}
	window.draw(backgroundSprites[0]);
	window.draw(backgroundSprites[1]);
	window.draw(backgroundSprites[2]);
	window.draw(backgroundSprites[3]);

	/*-----draw platforms------*/
	for (int i = 0; i < model->levelManager.platforms.size(); i++) {
		sf::VertexArray plat = model->levelManager.platforms[i]->plat;

		if (model->player->centered && model->player->centeredY) {
			plat[0].position = sf::Vector2f(CENTER_SCREEN + plat[0].position.x - model->player->position.x, model->levelManager.platforms[i]->y + height / 2 - model->player->position.y);
			plat[1].position = sf::Vector2f(CENTER_SCREEN + plat[1].position.x - model->player->position.x, model->levelManager.platforms[i]->y + height / 2 - model->player->position.y);
			plat[2].position = sf::Vector2f(CENTER_SCREEN + plat[2].position.x - model->player->position.x, model->levelManager.platforms[i]->y + 35 + height / 2 - model->player->position.y);
			plat[3].position = sf::Vector2f(CENTER_SCREEN + plat[3].position.x - model->player->position.x, model->levelManager.platforms[i]->y + 35 + height / 2 - model->player->position.y);
		}
		else if (model->player->centered) { //when player is centered, the platforms should not scroll with him..
			plat[0].position = sf::Vector2f(CENTER_SCREEN + plat[0].position.x - model->player->position.x, model->levelManager.platforms[i]->y);
			plat[1].position = sf::Vector2f(CENTER_SCREEN + plat[1].position.x - model->player->position.x, model->levelManager.platforms[i]->y);
			plat[2].position = sf::Vector2f(CENTER_SCREEN + plat[2].position.x - model->player->position.x, model->levelManager.platforms[i]->y + 35);
			plat[3].position = sf::Vector2f(CENTER_SCREEN + plat[3].position.x - model->player->position.x, model->levelManager.platforms[i]->y + 35);
		}

		sf::Texture platTex;
		platTex = imageManager.get_texture("Assets/grassHalf.png");
		platTex.setRepeated(true);
		window.draw(plat, &platTex);
	}

	/*-----handle the enemies-----*/
	for (int i = 0; i < model->levelManager.enemies.size(); i++) {
		sf::Sprite enemy = model->levelManager.enemies[i]->sprite;
		enemy.setTexture(imageManager.get_texture("Assets/goomba.bmp", sf::Color::White), true);
		if (model->player->centered) { //when player is centered, the goombas should not scroll with him..
			enemy.setPosition(CENTER_SCREEN + enemy.getPosition().x - model->player->position.x, enemy.getPosition().y);
		}
		if (model->player->position.y < height / 2) {
			enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y + height / 2 - model->player->position.y);
		}
		window.draw(enemy);
	}

	/*-----render stuff-----*/
	for (int i = 0; i < renderables.size(); i++) {
		window.draw(renderables[i]->sprite);
	}

	//BULLETS
	for (int i = 0; i < model->player->bullets.size(); i++) {
		sf::Sprite currBullet = model->player->bullets[i]->sprite;
		currBullet.setTexture(imageManager.get_texture("Assets/bulletRight.png"), true);
		if (model->player->centered) { //when player is centered, the goombas should not scroll with him..
			currBullet.setPosition(CENTER_SCREEN + model->player->bullets[i]->position.x - model->player->position.x, model->player->bullets[i]->position.y);
		}
		if (model->player->position.y < height / 2) {
			currBullet.setPosition(CENTER_SCREEN + model->player->bullets[i]->position.x - model->player->position.x, model->player->bullets[i]->position.y + height / 2 - model->player->position.y);
		}
		window.draw(currBullet);
	}

	ss.str(""); //clear and update score UI
	ss << "Score: " << model->score;
	text.setString(ss.str());
	hud->render(&window);
	window.draw(text);
	window.display();
}