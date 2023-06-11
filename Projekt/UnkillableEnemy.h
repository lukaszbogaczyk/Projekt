#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"
#include "Enemy.h"


class UnkillableEnemy : public Enemy
{

	const unsigned short speed = 1;
	short direction = -1;
	float y_velocity = 0;


public:
	UnkillableEnemy(float _x, float _y);
	void draw(sf::RenderWindow& _window) override;
	void update(Map& _map, Character& _character) override;
	bool onMap() override;

	friend class Map;
	friend class WallEnemy;
};