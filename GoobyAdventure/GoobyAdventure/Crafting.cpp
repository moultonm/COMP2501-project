#include "Crafting.h"
#include <iostream>
Crafting::Crafting() {
	select1 = 0;
	select2 = 0;
	toMake = 0;
	// load a font
	font.loadFromFile("Assets/arial.ttf");

	// set up the text at the top
	top.setFont(font);
	top.setString("CRAFTING");
	top.setCharacterSize(50);
	top.setFillColor(sf::Color::Black);
	top.setPosition(sf::Vector2f(275, 50));

	// set up the item description box text
	itemDesc.setFont(font);
	itemDesc.setString(""); // temporary
	itemDesc.setCharacterSize(15);
	itemDesc.setFillColor(sf::Color::Black);
	itemDesc.setPosition(sf::Vector2f(500, 200));

	// set up the crafted item name text
	craftName.setFont(font);
	craftName.setString(""); // temporary
	craftName.setCharacterSize(15);
	craftName.setFillColor(sf::Color::Black);
	craftName.setPosition(sf::Vector2f(450, 320));

	// set up the crafted item description text
	craftDesc.setFont(font);
	craftDesc.setString(""); // temporary
	craftDesc.setCharacterSize(15);
	craftDesc.setFillColor(sf::Color::Black);
	craftDesc.setPosition(sf::Vector2f(450, 450));

	// the items coming in are going to populate a vector, but they won't come in until later.
	// make the leftmost rectangle, make it grey
	left.setPosition(sf::Vector2f(50, 125));
	left.setSize(sf::Vector2f(200, 400));
	left.setOutlineColor(sf::Color(100, 100, 100));
	left.setOutlineThickness(5);
	left.setFillColor(sf::Color::White);

	// make the small left to craft rectangle, make the outline grey and inside white
	smallLeft.setPosition(sf::Vector2f(400, 125));
	smallLeft.setSize(sf::Vector2f(50, 50));
	smallLeft.setOutlineThickness(5);
	smallLeft.setOutlineColor(sf::Color(100, 100, 100));
	smallLeft.setFillColor(sf::Color::White);

	// make the small right rectangle, make the outline grey and inside white
	smallRight.setPosition(sf::Vector2f(500, 125));
	smallRight.setSize(sf::Vector2f(50, 50));
	smallRight.setOutlineThickness(5);
	smallRight.setOutlineColor(sf::Color(100, 100, 100));
	smallRight.setFillColor(sf::Color::White);

	// make the selected item box, with the outline pink and inside white
	itemSelector.setPosition(sf::Vector2f(60, 130));
	itemSelector.setSize(sf::Vector2f(180, 30));
	itemSelector.setOutlineColor(sf::Color::Magenta);
	itemSelector.setOutlineThickness(2);
	itemSelector.setFillColor(sf::Color::White);

	// make the moving selection box
	boxSelector.setPosition(sf::Vector2f(395, 120));
	boxSelector.setSize(sf::Vector2f(60, 60));
	boxSelector.setOutlineColor(sf::Color::Magenta);
	boxSelector.setOutlineThickness(2);
	boxSelector.setFillColor(sf::Color::White);

	// make the lower crafting box
	craftingLarge.setPosition(sf::Vector2f(400, 300));
	craftingLarge.setSize(sf::Vector2f(300, 200));
	craftingLarge.setOutlineThickness(5);
	craftingLarge.setOutlineColor(sf::Color(100, 100, 100));
	craftingLarge.setFillColor(sf::Color::White);

	// make the small inner box with grey outline, white inside
	smallCraft.setPosition(sf::Vector2f(525, 375));
	smallCraft.setSize(sf::Vector2f(50, 50));
	smallCraft.setOutlineThickness(5);
	smallCraft.setOutlineColor(sf::Color(100, 100, 100));
	smallCraft.setFillColor(sf::Color::White);

	// make the inner description box with grey outline, white inside
	craftNameBox.setPosition(sf::Vector2f(410, 310));
	craftNameBox.setSize(sf::Vector2f(280, 50));
	craftNameBox.setOutlineThickness(5);
	craftNameBox.setOutlineColor(sf::Color(100, 100, 100));
	craftNameBox.setFillColor(sf::Color::White);

	// make the description text, don't set string
	craftDescBox.setPosition(sf::Vector2f(410, 440));
	craftDescBox.setSize(sf::Vector2f(280, 50));
	craftDescBox.setOutlineThickness(5);
	craftDescBox.setOutlineColor(sf::Color(100, 100, 100));
	craftDescBox.setFillColor(sf::Color::White);

}

Crafting::~Crafting() {

}

void Crafting::render(sf::RenderWindow* window) {

	itemSelector.setPosition(60, 130 + index * 30);

	window->clear(sf::Color::White);
	window->draw(top);
	window->draw(left);
	window->draw(craftingLarge);
	window->draw(boxSelector);
	window->draw(itemSelector);
	window->draw(smallLeft);
	window->draw(smallRight);
	window->draw(smallCraft);
	window->draw(craftNameBox);
	window->draw(craftDescBox);
	window->draw(itemDescBox);
	window->draw(itemDesc);
	window->draw(craftName);
	window->draw(craftDesc);
	if (select1 != 0) {
		select1->sprite.setPosition(sf::Vector2f(400, 125));
		window->draw(select1->sprite);
	}
	if (select2 != 0) {
		select2->sprite.setPosition(sf::Vector2f(500, 125));
		window->draw(select2->sprite);
	}
	if (toMake != 0) {
		toMake->sprite.setPosition(sf::Vector2f(525, 375));
		window->draw(toMake->sprite);
	}
	for (int i = 0; i < itemToSel.size(); i++) {
		window->draw(itemToSel[i]);
	}
}

void Crafting::menu(std::vector<Item*>& items) {
	itemToSel.clear();
	itemToSel.reserve(items.size());
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->getTier() == 1) {
			itemToSel.push_back(sf::Text(items[i]->getName(), font, 15));
			itemToSel[itemToSel.size() - 1].setFillColor(sf::Color::Black);
			itemToSel[itemToSel.size() - 1].setPosition(62, 132 + i * 30);
		}
	}
}




void Crafting::craft(std::vector<Item*>& items) {
	//check what item one is against item two
	if (select1->getTier() != 1 || select2->getTier() != 1) {
		select1 = 0;
		select2 = 0;
		return;
	}

	if (select1->getName() == "bullet") {
		if (select2->getName() == "flux capacitor") {
			toMake = new Item(2, "fire gun");
			craftDesc.setString(toMake->getDef());
			craftName.setString(toMake->getName());
		}
		else {
			select1 = 0;
			select2 = 0;
			return;
		}
	}
	else if (select1->getName() == "flux capacitor") {
		if (select2->getName() == "bullet") {
			toMake = new Item(2, "fire gun");
			craftDesc.setString(toMake->getDef());
			craftName.setString(toMake->getName());
		}
		else {
			select1 = 0;
			select2 = 0;
			return;
		}
	}
	else {
		select1 = 0;
		select2 = 0;
		return;
	}
	items.push_back(toMake);
	select1 = 0;
	select2 = 0;
	itemDesc.setString("");
}