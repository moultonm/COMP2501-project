#include <iostream>
#include "Manager.h"

Manager::Manager() {

}

const sf::Texture & Manager::get_texture(std::string key, sf::Color mask) {

	if (textures.count(key) == 0) { //if this file isn't mapped yet, we'll add it

		sf::Image image;
		image.loadFromFile(key);

		std::cout << key << " loaded from file." << std::endl;

		if (mask != sf::Color::Transparent) { //if a mask was provided, we'll use it
			image.createMaskFromColor(mask);
		}

		textures.insert(std::pair<std::string, sf::Texture>(key, sf::Texture()));
		textures[key].loadFromImage(image);
	}
	return this->textures[key];
}
