#pragma once
#include "Global_variables.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Enemy.h"

//Header klasy Mapa

class WallEnemy;
class Enemy;

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
	std::vector<std::unique_ptr<Enemy>> Enemies;
	std::vector<sf::CircleShape> Powers;

	std::vector<sf::Sprite> draw(sf::RenderWindow& _window);
	void load_from_file(std::string map_directory);
	bool colision(const std::vector<Cell>& cells, sf::FloatRect bounds);
};
