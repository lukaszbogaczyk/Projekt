#pragma once
#include "Global_variables.h"
#include <SFML/Graphics.hpp>

//Header klasy Mapa

class Map
{
	mapVector map;

	sf::Texture brick_texture;
	sf::Texture spike_texture;
	sf::Texture cloud_texture;




public:
	Map();
	int map_width;
	int map_height;

	std::vector<sf::Sprite> draw(sf::RenderWindow& _window);
	void load_from_file(std::string map_directory);
};
