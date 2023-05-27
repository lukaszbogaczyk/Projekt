#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"
#include "Enemy.h"


class WallEnemy : public Enemy
{
	
	float speed = 1;
	float direction = -1;
	float y_velocity = 0;
	bool alive = true;
	

public:
	WallEnemy(float _x, float _y);
	void draw(sf::RenderWindow& _window) override;
	void update(Map& _map, Character& _character) override;
	bool onMap() override;
	bool on_map = true;

	friend class Map;
};