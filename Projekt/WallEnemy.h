#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Map.h"

class WallEnemy : public Enemy
{
	
	float speed = 0.5;
	float direction = -1;
	float max_gravity = 2;
	float y_velocity = 0;

public:
	WallEnemy(float _x, float _y);
	void draw(sf::RenderWindow& _window) override;
	void update(Map& _map) override;

	friend class Map;
};