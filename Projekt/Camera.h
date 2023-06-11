#pragma once
#include "Global_variables.h"
#include "Map.h"
#include "Character.h"
#include <SFML/Graphics.hpp>

class Camera
{
	unsigned short x;
	unsigned short y;

public:
	sf::View view;
	Camera();
	void update(Map& map, Character& character);
	friend class Character;
};
