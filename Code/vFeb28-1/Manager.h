#pragma once
#include <SFML/Graphics.hpp>

class Manager {
public:
	Manager();

	//for now a map of Filepath->Texture pairs are stored
	std::map<std::string, sf::Texture> textures;

	//get_texture method is called with a filepath and, optionally, a mask color
	const sf::Texture& get_texture(std::string, sf::Color = sf::Color::Transparent);
};
