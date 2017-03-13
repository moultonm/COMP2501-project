#pragma once
#include <SFML/Graphics.hpp>

class Updateable {
public:
	virtual void update(sf::Time) = 0;
	sf::Vector2f position; //updateables all have a location in the gameworld
};
