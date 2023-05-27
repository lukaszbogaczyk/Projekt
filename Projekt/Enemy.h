#pragma once
#include "Map.h"
#include <SFML/Graphics.hpp>

class Map;

class Enemy
{
protected:
	float x = 0;
	float y = 0;
	float gravity = 0.5;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	virtual void draw(sf::RenderWindow& _window) = 0;
	virtual void update(Map& _map) = 0;

	virtual ~Enemy() {}
};
